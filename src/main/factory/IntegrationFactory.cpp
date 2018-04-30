#include "Factory.h"

namespace Solver {
	class Integrator {
		public:
			Integrator(po::variables_map &vm);
		private:
			string integratorType;
	}	

	Integrator::Integrator(po::variables_map &vm){
		integratorType = vm["integration-type"].as<string>();
	}

	Integrator::Integrate(Solver::Stepper stepper, sequential::ode_system_function equation,
												storage_type & initialState, double startTime, double endTime, double stepSize,
												Observer observer){

		switch(integratorType){
			case "constant": 
				return integrate_const(
			    stepper,
			    equation,
			    initialState,
			    startTime,
			    endTime,
			    stepSize,
			    observer
  			);
  			break;

  		case "adaptive": 
				return integrate_adative(
			    stepper,
			    equation,
			    initialState,
			    startTime,
			    endTime,
			    stepSize,
			    observer
  			);
  			break;
		}



	}

	class Stepper {
		// TODO : Finish implementation
	}

}