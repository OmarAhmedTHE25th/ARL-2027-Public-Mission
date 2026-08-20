#include "safety_monitor.hpp"

#include <cmath>

namespace arl {
namespace {

bool isFinite(const Detection& detection) {
    return std::isfinite(detection.forward)
        && std::isfinite(detection.left)
        && std::isfinite(detection.confidence);
}

}  // namespace

std::vector<Obstacle> processDetections(
    const std::vector<Detection>& detections,
    const RoverPose& pose,
    const SafetyConfig& config)
{
    constexpr  double PI = 3.1415926535;
    std::vector<Obstacle> obstacles;
    const double headingRadians = pose.headingDegrees * (PI/180.00);
    const double cosine = std::cos(headingRadians);
    const double sine = std::sin(headingRadians);

    for (const auto & detection : detections) {
        const double range = std::hypot(detection.forward, detection.left);
        const bool validConfidence = detection.confidence >= 0.0
            && detection.confidence >= config.minimumConfidence && detection.confidence <= 1.0;
        const bool validRange = range > 0.0 && range <= config.maximumRangeMeters;

        if (!isFinite(detection) || !validConfidence || !validRange) {
            continue;
        }

        obstacles.push_back({
            detection.id,
            detection.forward,
            detection.left,
            pose.worldX + cosine * detection.forward - sine * detection.left,
            pose.worldY + sine * detection.forward + cosine * detection.left,
            range,
        });
    }

    return obstacles;
}

std::optional<Obstacle> findNearestObstacle(const std::vector<Obstacle>& obstacles) {
    if (obstacles.empty()) {
        return std::nullopt;
    }

    const Obstacle* nearest = &obstacles.front();
    for (const auto& obstacle : obstacles) {
        if (obstacle.range < nearest->range) {
            nearest = &obstacle;
        }
    }

    return *nearest;
}

double calculateStoppingDistance(double speedKph, const SafetyConfig& config) {

    const double speedMps = speedKph / 3.6;
    const double reactionDistance = speedMps * config.reactionTimeSeconds;
    const double brakingDistance = speedMps * speedMps
        / (2.0 * config.maximumDecelerationMps2);
    return reactionDistance + brakingDistance;
}

bool shouldEmergencyBrake(const std::vector<Obstacle>& obstacles, double speedKph, const SafetyConfig& config) {
    const auto stoppingDist = calculateStoppingDistance(speedKph,config);
    for (const auto &obstacle: obstacles) {
        if (obstacle.forward >= 0.0 &&
            fabs(obstacle.left) <= config.laneHalfWidthMeters &&
            obstacle.forward <= stoppingDist) return true;

    }
    return false;
}
}  // namespace arl