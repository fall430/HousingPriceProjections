# HousingPriceProjections

HousePriceProjections is a machine learning project developed in C, designed to estimate house prices using a one-shot learning algorithm. Leveraging matrix operations, dynamic memory allocation, and the Unix environment, this project demonstrates a practical application of machine learning techniques to real-world data scenarios.

Overview
In the age of digital transformation, machine learning is at the forefront of innovation, automating processes and providing data-driven insights. HousePriceProjections is a simple yet powerful example of how machine learning can be used to predict house prices based on historical data. By implementing a one-shot learning algorithm, this project showcases how data attributes such as the number of bedrooms, bathrooms, square footage, and construction year can be utilized to estimate market prices.

Features
One-Shot Learning Algorithm: Utilizes a one-shot learning technique to derive weights from historical data, allowing for quick and efficient model training.
Matrix Operations: Implements essential matrix operations, including multiplication, transposition, and inversion, critical for computing weight estimations.
Dynamic Memory Management: Demonstrates the use of dynamic memory allocation in C, optimizing memory usage for handling large datasets.
Unix Environment: Built and tested in a Unix environment, making use of standard system tools and libraries.
How It Works
Training Data Input: The program takes a set of training data, including house attributes and corresponding prices.

Weight Calculation: Using the provided data, the program computes the weights for each attribute using the formula:

W = (X^T * X)^(-1) * X^T * Y

where X is the matrix of house attributes, Y is the matrix of prices, and W is the matrix of weights.

Price Prediction: Once the weights are determined, they can be applied to a new set of house attributes to predict their prices.
