#include "MyModel.h"
#include "RandomNumberGenerator.h"
#include "Utils.h"
#include "Data.h"
#include <cmath>

using namespace std;
using namespace DNest3;

MyModel::MyModel()
{

}

void MyModel::fromPrior()
{
	A = exp(tan(M_PI*(0.97*randomU() - 0.485)));
	T = exp(tan(M_PI*(0.97*randomU() - 0.485)));
	phi = 2.*M_PI*randomU();
	period = exp(tan(M_PI*(0.97*randomU() - 0.485)));
	phase = randomU();
	depth = exp(tan(M_PI*(0.97*randomU() - 0.485)));
	width = exp(tan(M_PI*(0.97*randomU() - 0.485)));
	sigma = exp(tan(M_PI*(0.97*randomU() - 0.485)));
}

double MyModel::perturb()
{
	int which = randInt(8);

	if(which == 0)
	{
		A = log(A);
		A = (atan(A)/M_PI + 0.485)/0.97;
		A += randh();
		wrap(A, 0., 1.);
		A = tan(M_PI*(0.97*A - 0.485));
		A = exp(A);
	}
	if(which == 1)
	{
		T = log(T);
		T = (atan(T)/M_PI + 0.485)/0.97;
		T += randh();
		wrap(T, 0., 1.);
		T = tan(M_PI*(0.97*T - 0.485));
		T = exp(T);
	}
	if(which == 2)
	{
		phi += randh();
		wrap(phi, 0., 2.*M_PI);
	}
	if(which == 3)
	{
		period = log(period);
		period = (atan(period)/M_PI + 0.485)/0.97;
		period += randh();
		wrap(period, 0., 1.);
		period = tan(M_PI*(0.97*period - 0.485));
		period = exp(period);
	}
	if(which == 4)
	{
		phase += randh();
		wrap(phase, 0., 1.);
	}
	if(which == 5)
	{
		depth = log(depth);
		depth = (atan(depth)/M_PI + 0.485)/0.97;
		depth += randh();
		wrap(depth, 0., 1.);
		depth = tan(M_PI*(0.97*depth - 0.485));
		depth = exp(depth);
	}
	if(which == 6)
	{
		width = log(width);
		width = (atan(width)/M_PI + 0.485)/0.97;
		width += randh();
		wrap(width, 0., 1.);
		width = tan(M_PI*(0.97*width - 0.485));
		width = exp(width);
	}
	if(which == 7)
	{
		sigma = log(sigma);
		sigma = (atan(sigma)/M_PI + 0.485)/0.97;
		sigma += randh();
		wrap(sigma, 0., 1.);
		sigma = tan(M_PI*(0.97*sigma - 0.485));
		sigma = exp(sigma);
	}

	return 0.;
}

double MyModel::logLikelihood() const
{
	const vector<double> t = Data::get_instance().get_t();
	const vector<double> y = Data::get_instance().get_y();

	double logL = 0.;

	double mu;
	for(size_t i=0; i<y.size(); i++)
	{
		// The big signal
		mu = A*sin(2.*M_PI*t[i]/T + phi);

		// The transit
		if(mod(t[i] + 0.5*width + phase*period, period) < width)
			mu -= depth;

		logL += -0.5*log(M_PI) - log(sigma)
				-0.5*pow((y[i] - mu)/sigma, 2);
	}

	return logL;
}

void MyModel::print(std::ostream& out) const
{
	out<<A<<' '<<T<<' '<<phi<<' ';
	out<<period<<' '<<phase<<' '<<depth<<' '<<width<<' ';
	out<<sigma<<' ';
}

string MyModel::description() const
{
	return string("A, T, phi, period, phase, depth, width, sigma");
}

