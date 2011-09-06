#include"simulation.h"

simulation::simulation()
{

}

simulation::~simulation()
{

}

void simulation::rebuild()
{

}

bool simulation::execute(string dna, uint32 sim_id)
{
    string bin = conf->simulator_bin , sim_path = get_sim_path(sim_id);
    char *buffer = new char[1024];
    int ret;

    setup_input_file(dna, sim_id);

    getcwd(buffer,1024);

    ret = chdir((char *)sim_path.c_str());
    if(ret)
        perror("chdir");

    if (!file_exists(bin))
    {
        cout << "simulator binary does not exists." << endl;
        exit(0);
    }

    bin.insert(0,"./");
    bin += " ";
    bin += conf->simulator_args;
    bin += conf->test_file_out;
    bin += " > /dev/null 2>&1";
    ret = system(bin.c_str()); //int execl(path.c_str(), argvs);
    ret = chdir(buffer);
    if(ret)
        perror("chdir");

    delete[] buffer;
    return true;
}

bool simulation::setup_input_file(string dna, uint32 id)
{
    fstream sim_file;
    
    sim_file.open(get_input_file_path(id).c_str(),  fstream::out);

    if (!sim_file.is_open())
    {
        perror("input_file");
        exit(0);
    }

    int clocks = GetStrRowSize(dna);
    int inputs = GetStrColSize(dna);
    
    if (conf->debug && conf->print_simulation)
    {
        cout << "clocks: " << clocks << endl;
        cout << "inputs: " << inputs << endl;
    }
    
    stringstream out;
    out << clocks;

    sim_file << out.str();
    sim_file << ";" << endl;

    for (uint32 i = 0 ; i < inputs; i++)
    {
        for (uint32 j = 0 ; j < clocks; j++)
        {
            sim_file << dna.c_str()[i * (clocks +1) + j];
            if (j != (clocks - 1))
                sim_file << ",";
        }
        sim_file << ";" << endl;
    }

    sim_file.close();
    return true;
}

string simulation::read_output(uint32 id)
{
    uint32 length;
    ifstream sim_out_file;
    string content;
    char *buffer = NULL;

    sim_out_file.open (get_output_file_path(id).c_str(), ios::binary );

    if (conf->debug && conf->print_simulation)
    {
        cout << "out : " << get_output_file_path(id).c_str() << endl;
    }
    
    if (!sim_out_file.is_open())
    {
        throw "Error output_file not found or can't open";
        
        //perror("output_file");
        //cout << "out : " << get_output_file_path(id).c_str() << endl;
        //exit(0);
    }

    sim_out_file.seekg (0, ios::end);
    length = sim_out_file.tellg();
    sim_out_file.seekg (0, ios::beg);

    buffer = new char[length + 1];

    sim_out_file.read (buffer,length);
    sim_out_file.close();
    remove(get_input_file_path(id).c_str()); // DEBUG mi assicuro che il vecchio file di ingresso venga rimosso
    buffer[length] = 0;
    content = buffer;
    delete[] buffer;
    
    return content;
}

void simulation::get_results(uint32 id, uint32& n_total_faults, uint32& n_faults)
{
    int ret;
    string str = read_output(id);
    char *str_s = strstr ((char *)str.c_str(),"0,");

    n_total_faults = 0; // se si rimuove questo nn funziona nulla (forse ora è ok ma non ci conterei)
    n_faults = 0;
    
    ret = sscanf(str_s, "0,%d.0\n1,%d.0\n", (int*)&n_total_faults, (int*)&n_faults);
    if (ret != 2)
        cout << "parsing error... ret " << ret << endl;

    if (conf->debug && conf->print_simulation)
    {
        cout << "#total_faults " << n_total_faults << endl;
        cout << "#faults_detected " << n_faults << endl;
    }
    if (n_total_faults > 1000)
        exit(0);

    remove(get_output_file_path(id).c_str());
}
