# Kalman Filter
- What do you know about Kalman Filters? Describe how it can be used in vehicle localization with a block diagram showing the estimation loop.

A Kalman Filter is an optimal estimation algorithm that predicts the state of a dynamic system (like a vehicle's position) by combining noisy sensor measurements with a mathematical model of the system. 
It works in two recurring steps:
1. Prediction: The filter uses the system's physics model to guess where the vehicle should be based on previous movements (e.g., "I was here, moving at this speed, so I should be there now"). This step increases uncertainty.
2. Update (Correction): The filter takes new sensor data (like GPS) and compares it to the prediction. It calculates a "Kalman Gain" to decide how much to trust the prediction vs. the new measurement to arrive at a final, more accurate estimate.

Estimation Loop:
[ Previous State ] ➔ [ Predict Step (Model) ] ➔ [ Predicted State & Uncertainty ]
                                                     │
                                                     ▼
[ Sensor Measurement ] ➔ [ Update Step (Kalman Gain) ] ◄─┘
                                 │
                                 ▼
                          [ Estimated State ] ➔ (Returns to Previous State for next loop)

# Localization Setup
- Imagine you're working on a self-driving car project and need to localize a vehicle in an unknown environment using a Kalman filter. Which states would you choose to estimate, and what types of sensors would you use to obtain the necessary data?

States to Estimate:
- Position: $(x, y, z)$ coordinates.
- Orientation (Heading/Attitude): Roll, pitch, and yaw ($\psi$).
- Velocity: Linear velocity ($v_x, v_y, v_z$) and angular velocity.
- Acceleration: To help predict rapid changes in motion.

Sensors to Use:
- IMU (Inertial Measurement Unit): Provides high-frequency data on acceleration and angular velocity (used for prediction).
- GNSS/GPS: Provides absolute position coordinates (used for updates).
- Wheel Encoders (Odometry): Measures how far wheels have turned to estimate distance traveled.
- LiDAR/Cameras: Used for visual or laser odometry by tracking features in the environment.

# SLAM Concepts
- Explain the concept of SLAM, mentioning different types of it.

SLAM (Simultaneous Localization and Mapping) is the computational problem of building or updating a map of an unknown environment while simultaneously keeping track of an agent's location within it. It's essential for robots in environments where GPS is unavailable (indoor, underground, or deep space).

Types of SLAM:
- EKF-SLAM: Uses Extended Kalman Filters to track the robot's pose and the positions of landmarks.
- Graph-Based SLAM: Represents the robot's path and landmarks as nodes in a graph, with sensor measurements as constraints between them. It optimizes the whole graph to find the most likely map.
- Visual SLAM (vSLAM): Uses cameras as the primary sensor.
- LiDAR SLAM: Uses laser scanners to create high-resolution 3D maps.

# Mapping and Sensor Selection
- How can we build a map in SLAM? What type of sensors might be useful for doing this task?

Building a map involves:
1. Feature Extraction: Identifying unique landmarks (corners, walls, specific objects).
2. Data Association: Matching observed features with previously seen ones to recognize the robot is in a known location.
3. Map Update: Adding new landmarks to the map and refining the positions of old ones based on new observations.

Useful Sensors:
- LiDAR: Excellent for precise distance measurements and building 2D/3D occupancy grids.
- Cameras: Cheap and provide rich semantic information (color, texture).
- Depth Cameras (RGB-D): Provide both images and distance per pixel.
- Sonar/Ultrasonic: Useful in specific environments like underwater.

# SLAM Localization Methods
- How does SLAM perform vehicle localization in an unknown environment? Discuss in two different types of SLAM.

Localization in SLAM works by comparing what the robot "sees" now to the map it has built so far.

1. Particle Filter SLAM (e.g., Gmapping): The robot maintains many "hypotheses" (particles) of where it might be. As it moves and takes measurements, it discards particles that don't match the sensor data and keeps those that do. The cluster of surviving particles represents the estimated location.
2. Graph-SLAM: The robot stores its history as a series of connected poses. When it returns to a previously visited spot ("Loop Closure"), it recognizes the similarity. It then runs an optimization algorithm to "snap" the path and map into a consistent shape, correcting all accumulated drift in its estimated position.