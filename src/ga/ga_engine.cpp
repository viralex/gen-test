#include "ga_engine.h"

ga_engine::ga_engine()
{
    generation = 0;
    srand(time(NULL));
}

ga_engine::~ga_engine()
{
    delete pop;
}

void ga_engine::init()
{   
    if (conf->verbose)
        cout << "init population" << endl;
    pop = new population();
    
    if (conf->verbose)
        cout << "selecting " << conf->population_size << " random individuals..." << endl;
    pop->new_random_population();
}


void ga_engine::evolve()
{
    float best_fitness = 0;
    string generations_logfile;
    
    if (!conf)
    {
        cout << "GA parameters aren't configured." << endl;
        return;
    }

    if (conf->verbose)
        cout << "the population is going to evolve for " << conf->max_generations << \
            " generations!" << endl << endl;

    while ( generation++ < conf->max_generations ) 
    {
        if (conf->verbose)
            cout << endl << "generation: " << generation << endl;
        if (conf->verbose && conf->print_population_size)
            cout << endl << "population: " << pop->size() << endl;
   
        best_fitness = pop->get_best_fitness();
        
        if (conf->verbose && conf->print_best_fitness)
            cout << "best_fitness: " << best_fitness << endl;

        if (conf->verbose && conf->print_best_dna)
            pop->print_best();
            
        if (conf->verbose)
            cout << "mating_individuals" << endl;
        pop->mate_individuals();

        if (conf->verbose)
            cout << "mutate_individuals" << endl;
        pop->mutate_individuals();

        if (conf->verbose)
            cout << "calc_population_fitness" << endl;
        pop->calc_population_fitness();
        
        if (conf->verbose)
            cout << "logging generation to file" << endl;
        if (conf->verbose)
        {
            generations_logfile = "logs/generation";
            stringstream out;
            out << generation;
            generations_logfile.append(out.str());          
            generations_logfile.append(".log");
            
            pop->log_population(generations_logfile);
        }
        
        if (conf->verbose)
            cout << "iteration end" << endl;
    }
}
