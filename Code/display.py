from pylab import *

data = loadtxt('fake_data.txt')
posterior_sample = atleast_2d(loadtxt('posterior_sample.txt'))

ion()
for i in xrange(0, posterior_sample.shape[0]):
  y = posterior_sample[i, 0]\
            *sin(2.*pi*data[:,0]/posterior_sample[i,1] + posterior_sample[i,2])

  hold(False)
  plot(data[:,0], data[:,1], 'b.', markersize=1)
  hold(True)

  period, phase, depth, width = posterior_sample[i, 3:-1]  
  which = nonzero(mod(data[:,0] + 0.5*width + phase*period, period) < width)[0]
  y[which] -= depth
  plot(data[:,0], y, 'r')
  title((i+1))
  draw()

ioff()
show()

