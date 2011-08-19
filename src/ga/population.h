#ifndef POPULATION_H
#define POPULATION_H

#include <cstdio>
#include <iostream>
#include <sstream>
#include <list>

#include "individual.h"
#include "../simulation/general_tests.h"

using namespace std;

typedef std::map<uint32, uint32>       weight_map;
typedef std::map<uint32, individual*>  individual_map;
typedef std::pair<uint32, individual*> individual_pair;
typedef std::list<uint32>              individual_id_list;

extern config *conf;

//! Contenitore della popolazione
/**
 *
 */

class population
{
    individual_map*     pool;
    individual_id_list  mating_pool;
    individual_map*     temp_pool;
    
    general_tests test;

    individual* get_random_individual() const;
    individual* new_random_individual();
    
    void    create_mating_pool();
    void    crossover(individual*&, individual*&);


    void    empty_population();
    
    public:
    population();
    ~population();
    
    void    new_random_population();

    void    execute_tests();
    void    read_faults();
    void    calc_population_fitness();
    float   get_avg_fitness() const;
    float   get_best_fitness() const;
    void    sort_by_fitness();  // deprecated

    void    transfert_bests();
    void    mate_individuals();
    void    mutate_individuals() const;  // deprecated
    void    mutate_individual(individual*);

    uint32  size() const;
    void    print_best() const;
    void    log_population(uint32 generation) const;
    void    cout_population(string logfile) const;
};

#endif
