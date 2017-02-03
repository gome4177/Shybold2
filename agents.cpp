
#include <iostream>
#include <algorithm>
#include <fstream>

#include "agents.h"

void agent::update() {
  double closex;
  double ix;
  double iy;
  double closey;
  double near_pred_x;
  double nearest_pred_x;
  double near_pred_y;
  double nearest_pred_y;
    std::vector<double> inputs;
     for (int i; i<input_agent.size(); i++){
       // if (input_agent.size() >=2) { //change this (loop througth input_agents and push_back onto inputs
	 // while (input_agent.size()<input_agents)
	   // const std::shared_ptr<agent> n;
	 // n< input_agents;
	 /*	 inputs = {( 10*((input_agent[0])->x - x))/sensing_range_pred    , (10*((input_agent[0])->y - y))/sensing_range_pred, 1, 10*(input_agent[0]->x-input_agent[0+1]->x)/sensing_range_pred, 10*(input_agent[0]->y-input_agent[0+1]->y)/sensing_range_pred};
	 //  std::cout<< 10*((input_agent[0])->x - x)<<"\n";
	 */
       if (input_agent.size()!=0 && input_agent[0]){
	   saw_pred=true;
	 inputs={};
	 for (int i=0;i<input_agents;i++){
	   
	   inputs.push_back(10*((input_agent[i])->x - x)/sensing_range_pred);
	     inputs.push_back(10*((input_agent[i])->y - y)/sensing_range_pred);
	 (10*((input_agent[0])->x - x)/sensing_range_pred) == closex;
	 (10*((input_agent[i])->x - x)/sensing_range_pred)== ix;
	 closex-ix==near_pred_x;
	 if (nearest_pred_x<near_pred_x && nearest_pred_x!=0){
	   (nearest_pred_x==nearest_pred_x);
	   }
	 else(nearest_pred_x==near_pred_x);

	
         (10*((input_agent[0])->y - y)/sensing_range_pred) == closex;
         (10*((input_agent[i])->y - y)/sensing_range_pred)== iy;
         closex-iy==near_pred_y;
         if (nearest_pred_y<near_pred_y && nearest_pred_y!=0){
           (nearest_pred_y==nearest_pred_y);
	 }
         else(nearest_pred_y==near_pred_y);






	 
	 }
	 inputs.push_back(nearest_pred_x);
	 
	   inputs.push_back(nearest_pred_y);
	 inputs.push_back(1.0);//bias node
     } else {
        //make appropariate number of inputs
	 saw_pred = false;
	 inputs = {10*((input_agent[i])->x - x)/sensing_range_pred,10*((input_agent[i])->y - y)/sensing_range_pred, 0.0, 0.0, 1.0};
	    }
    //you hand it chrome 1 values and chrome 2 values from genome
    n->update( (g->c1)->values, (g->c2)->values, inputs);
    //move based on ouptputs
    move_x_y(n->output_values[0] * pred_capture,  n->output_values[1] * pred_capture);
}	    
}
//Need to change to get sorted vector of agents inputs
void agent::getNearestAgentPrey(const std::shared_ptr<agent> &a) {
    if (input_agent.size() == 0) {
        if (this->distance(a) < sensing_range_prey) {
            input_agent.push_back(a);
	    std::cout <<distance(a)<<"/n";
        }
    } else if (this->distance(a) < this->distance(input_agent[0]) || !input_agent[0]->alive) {
        //change it here, sort the input_agents and push them appropriately on
        if (this->distance(a) < sensing_range_prey) {
	  
	 
	      input_agent[0] = a;
	      input_agent.push_back(a);   
	}
    }
}

void agent::getNearestAgentPred(const std::shared_ptr<agent> &a) {
    if (input_agent.size() == 0) {
        if (this->distance(a) < sensing_range_pred) {
            input_agent.push_back(a);
        }
    } else if (this->distance(a) < this->distance(input_agent[0]) || !input_agent[0]->alive) {
        //same thing here
        if (this->distance(a) < sensing_range_pred) {
            input_agent[0] = a;
	    input_agent.push_back(a);
        }
    }
}

//figure out what you want to do here
void agent::consume(int time) {
    if (input_agent.size() != 0) {
        if (this->distance(input_agent[0]) < pred_capture && input_agent[0]->alive) {
            input_agent[0]->alive = false;
            input_agent[0]->lastTime = time;
            ++fitness;
        }
    }
}

void agent::move_x_y(double dx, double dy) {
    x = std::max(0.0, std::min(x + dx, sizeX));
    y = std::max(0.0, std::min(y + dy, sizeY));
    
}

void agent::output_data(std::fstream &o, bool prey, int gen, int index) {

    o << gen << '\t';
    o << index << '\t';
    if (prey) {
        o << lastTime << '\t';
    } else {
        o << fitness << '\t';
    }
    
    for (int i = 0; i < geneNN; ++i) {
        o << ((g->c1)->values[i] + (g->c2)->values[i])/2.0 << '\t';
    }

    o << ((g->c1)->metabolic + (g->c2)->metabolic)/2.0 << '\t';
    o << ((g->c1)->radius + (g->c2)->radius) /2.0 << '\t';
    
    if (prey) {
        o << calcFitnessPrey() << '\n';
    } else {
        o << calcFitnessPred() << '\n';
    }
}
