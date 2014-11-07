from pylab import *

"""
Code to generate some fake transit data using a simple toy model.
"""

# RNG seed
seed(0)

# Lots of data points
N = 10001

# Timestamps (think in years)
t = linspace(0., 3., N)

# A big overall signal
y = 2*sin(2.*pi*t/3.)

# Add the transit
period = 1.
phase = 0.2 # (between 0 and 1)
depth = 0.1
width = 0.02
which = nonzero(mod(t + 0.5*width + phase*period, period) < width)[0]
y[which] -= depth

# Plot the noise-free model
plot(t, y, 'r', linewidth=1)

# Add noise
sigma = 0.1
y += sigma*randn(N)

# Plot the data
plot(t, y, 'b.', markersize=1)
xlabel('Time (years)', fontsize=16)
ylabel('Brightness', fontsize=16)
show()

