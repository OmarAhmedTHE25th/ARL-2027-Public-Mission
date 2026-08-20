# Perception Sensors
- Explain the working principles (i.e. how they capture data from the environments, the type of data captured, data processing requirements, etc.) of radars, lidars, and cameras.

Radars:
Standing for Radio Detection and Ranging, they have a device called an FMCW Tranciever which sends high-powered radio waves which travel at the speed of light and an antenna focuses these waves into narrow beams 
these radio waves collide with an object until they hit an object, then when the wave gets reflected back, the antenna catches these waves and sends them to a computer.
Which then analyzes the speed, time, and signal strength of the waves to come to determine the location of that object and a rough indicator of the reflectivity/material of that object.
These signals are processed using:
ADC to convert the analog signals to digital ones
Fast Fourier Transform to determine the frequency components
Doppler processing to estimate velocity
Noise filtering

Lidars:
Standing for Light Detection and Ranging, similar to a radar, but instead of radio waves they send rapid pulses of laser light at a target object or surface and measuring the time it takes for the reflection to return.
And because the wavelength of light is much smaller than radio waves, they can create hyper-detailed, high-resolution 3D images (point clouds)
Each pulse of light is measured for the time between transmission and receiving, multiplied by the speed of light divided by 2 (since the time is for a round trip) to get the distance of the object:
$d = \frac{c \cdot \Delta t}{2}$
Then the LiDAR changes directions and for each pulse, the LiDAR knows:
distance 
horizontal angle
vertical angle 
So every measurement can be converted into a 3D coordinate:
(x,y,z)
repeating the same process up to millions of times per second
Its main weakness is that laser light can be affected by heavy rain, fog, snow, and dust.
Processing LiDAR data involves:
Converting time-of-flight measurements into distances
Converting polar/spherical measurements into Cartesian coordinates
Point-cloud filtering
Removing noise/outliers
Ground detection
Clustering
Object detection
Object tracking
3D mapping

Cameras:
A camera passively measures light coming from the environment, light enters the camera through the lens and reaches an image sensor.
The lens focuses that light so it lands sharp on the sensor instead of a blurry mess.
The light sensor has millions of photodiodes that convert brightness to electricity.
Since photodiodes are colorblind, most sensors put a colored filter over each pixel either red,green, or blue
Each pixel now only captures one color channel. 
Then the camera's processor looks at neighboring pixels to make an educated guess mathematically on what the full color should be at each point
The processor then applies noise reduction, sharpening, white balance, and compression (like JPEG), and writes it to the memory card

# Stereo Vision
- Explain how two cameras can be used to get 3D position information about objects.  
A normal camera doesn't directly know depth, which means that depth has to be inferred.
Stereo vision uses 2 cameras with a known distance between them called a baseline
an object is seen at different horizontal positions by each camera the difference in the horizontal positions is called a disparity ($d = x_L - x_R$ )
Nearby objects have a bigger disparity compared to faraway objects
The cameras send the data it gathered to an external computer (sometimes it's an internal processor) including:
- The distance between the cameras $B$
- The camera's focal length $f$
- The measured disparity $d$

Then the computer measures the depth from triangulation, using the formula:
$Z = \frac{f \cdot B}{d}$
And this process is repeated for the millions of pixels finding the disparity and depth, these findings can be turned into a depth map
where different values represent different depths.And from that, a 3D image can be constructed
# Machine Learning
- What are neural networks? How do they learn?
- How can neural networks be used to aid with processing sensor data for environment perception?  

At the basic level, neural networks are layers of interconnected mathematical units called neurons each neuron has inputs, output(s), weights, and a bias
Each neuron calculates the output using the formula:
$y = f(\sum_{i=1}^{n} x_i w_i + b)$
where:
- $y$ = output
- $x_i$ = input(s)
- $w_i$ = weight(s)
- $b$ = bias
The main parts of a neural network are
- Input layer: it takes in raw data like raw pixels in an image or words of a text
- Hidden layers: Do the main math work in the middle. They find patterns and features.
- Output layer: Gives the final answer or prediction.
- Weights and biases: Numbers that change the strength of connections as the network learns

Each neuron does a weighted sum and passes that sum to an activation function (commonly ReLU or Sigmoid) and then passes the output to the other neurons
and each neuron does the same it takes inputs from previous nodes, does a weighted sum on these inputs adds a bias
and passes the sum to an activation function (otherwise the network would only be capable of drawing straight lines) and then passes it to the next neuron.
This process is called a forward pass 
After a network makes a prediction, a Loss function is applied to the output(s) of the network to determine how wrong it was.
An example of a loss function is MSE (Mean Squared Error):
$MSE = \frac{1}{n} \sum_{i=1}^{n} (y_i - \hat{y}_i)^2$
Then the network works its way backwards calculating the gradients for each neuron using the derivative of the output with respect to the weight, and since neural networks often have millions of neurons, 
these derivatives are chained since each neuron depends on the neuron before it.
Once the network has all the gradients, it updates every weight like this:
new weight = old weight - (learning rate × gradient)
The learning rate is a small number (like 0.01) that controls how big each step is. Too big, and it overshoots and bounces around. 
Too small and training takes too much time.
The gradient tells the slope; which direction makes the loss go up. So the network goes in the opposite direction, hence "descent."
This process is called back propagation, a way for the network to correct itself after making a wrong prediction.

Now neuron networks can be invaluable when combined with sensors; 
Cameras output an image, which is a grid of pixels; an image is fed to a Neural Network (specifically a Convolutional Neural Network)
Instead of connecting every neuron to every pixel, CNNs slide small filters across the image to detect local patterns; edges, textures, shapes; then build up from there to high-level understanding.
Tasks:
Object detection (where are things and what are they)
Semantic segmentation (label every single pixel by category)
Depth estimation (guess distance from a 2D image)

Radar produces measurements that can be relatively difficult to interpret directly.
A neural network can learn patterns in radar data and help identify:
- Cars
- Pedestrians
- Cyclists
- Other objects
- Object trajectories
- False detections
For example,
Radar measurements
↓
Neural Network
↓
"Car moving at 32 km/h"

LiDAR produces a 3D point cloud representing the environment.
Networks like PointNet were specifically designed to process unordered point clouds directly and extract 3D structure from them.

IMU / accelerometers / gyroscopes
These output time-series data; sequences of readings over time. Recurrent Neural Networks (RNNs) or more modernly Transformers handle sequential data well, 
picking up on patterns across time like recognizing motion gestures or detecting anomalies in vibration patterns.

A key technique used is sensor fusion; instead of providing a NN one sensor's data, we provide for it multiple sensors
Each sensor provides different information.
For example,
A camera provides an image of a pedestrian
A LiDAR provides that the object is 18 meters away and provides its 3D shape.
A Radar provides that the speed of the object is 2 m/s
The neural network can learn how to combine those measurements.
to form a full idea of the environment “A pedestrian 18 meters away moving toward us at 2 m/s with this image”

