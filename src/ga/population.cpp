#include "population.h"

population::population()
{
    if (conf->population_size == 0)
    {
        cout << "can't use zero population size" << endl;
        exit(0);
    }
    
    if (conf->chromosome_start_len == 0)
    {
        cout << "can't use zero gene length" << endl;
        exit(0);
    }

    if (conf->chromosome_start_len == 0)
    {
        cout << "can't use zero chromosome length" << endl;
        exit(0);
    }
}

population::~population()
{
    for (list<individual*>::iterator it = pool.begin(); it != pool.end(); it++)
    {
        if (*it) 
            delete *it;
    }
}

individual* population::get_random_individual() const
{
    individual *i = NULL;
    int rnd = rand()%pool.size() + 1, count = 0;
    
    
    list<individual*>::const_iterator it = pool.begin();
    for (it = pool.begin(); it!=pool.end(); ++it)
    {
        if (count == rnd)
        {
            i= *it;
            break;
        }
        count++;
    }  
    
    return i;
}

individual* population::new_random_individual()
{
    individual *i = new individual(conf->chromosome_start_len, conf->chromosome_start_len);
    
    if (i)
        i->dna_random();

    return i;
}

void population::new_random_population()
{
    int created = 0;
    
    while (created++ < conf->population_size)
        pool.push_back(new_random_individual());
}

void population::calc_fitness()
{

}

float population::get_avg_fitness() const
{
    float sum_fitness = 0;
    list<individual*>::const_iterator it = pool.begin();
    
    for (it = pool.begin(); it!=pool.end(); ++it)
    {
        sum_fitness+=(*it)->get_fitness();
    }  
    
    if (pool.size() == 0)
        return 0;
    else 
        return sum_fitness/pool.size();
}

float population::get_best_fitness() const
{
    list<individual*>::const_iterator it = pool.begin();
    return (float)(*it)->get_fitness();
}

void population::sort_by_fitness()
{
    pool.sort();
}

void population::mate_individuals()
{
    for (int i=0; i<(rand()%100+1); i++) // temporaneo per testare kill_individuals
    {
        pool.push_back(new_random_individual());    
    }
}


void population::mutate_individuals() const
{
    list<individual*>::const_iterator it = pool.begin();
    float mutate_probability = conf->mutation_rate*100;
    float rnd;
    
    for (it = pool.begin(); it!=pool.end(); ++it)
    {
        rnd = rand()%100 + 1; 
        
        if (mutate_probability > rnd)
        {
            if (conf->verbose && conf->print_mutations)
                cout << "mutation event!"<<endl;

            (*it)->dna_mutate(conf->mutation_strength);
        }
    }  
}

void population::kill_individuals(uint32 howmany)
{
    list<individual*>::iterator it = pool.begin();
    if (pool.size() > conf->population_size)
    {
        if (conf->verbose && conf->print_kills)
            cout << "killing: " << (pool.size() - conf->population_size) << endl;
        
        advance(it, conf->population_size);
        pool.erase(it, pool.end());
    }
}

uint32  population::size() const
{
    return pool.size();
}

void population::print_best() const
{
    list<individual*>::const_iterator it = pool.begin();
    cout << (*it)->get_dna();
}

