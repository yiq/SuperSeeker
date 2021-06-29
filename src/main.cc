#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <vector>
#include <set>
#include <htslib/vcf.h>
#include <htslibpp.h>
#include <htslibpp_variant.h>

#include "typedefs.h"
#include "vcf_parser.h"
#include "vcf_print.h"
#include "supertree.h"

using namespace YiCppLib::HTSLibpp;

int main(int argc, char** argv) {

    auto vcf = htsOpen(argv[1], "r");
    auto header = htsHeader<bcfHeader>::read(vcf);

    // ensure vcf has "AFCLU" field
    auto has_afclu = std::any_of(
            htsHeader<bcfHeader>::dictBegin(header, htsHeader<bcfHeader>::DictType::ID),
            htsHeader<bcfHeader>::dictEnd(header, htsHeader<bcfHeader>::DictType::ID),
            [](auto id_field){ return strcmp(htsProxy(id_field).key(), "AFCLU") == 0; });

    if(!has_afclu) {
        std::cout<<"the given vcf file does not have AFCLU (allele frequency cluster annotation)"<<std::endl;
        exit(1);
    }

    // parse vcf file for samples, clusters, and cluster allele frequencies
    std::vector<std::string> samples;
    std::set<std::string> af_clusters;
    af_table_t af_table;

    parse_vcf(vcf, header, samples, af_clusters, af_table);

    for(auto& c : af_clusters) std::cerr<<"\t"<<c;
    std::cerr<<std::endl;
    for(auto& s : samples) {
        std::cerr<<s;
        for(auto& c : af_clusters) std::cerr<<"\t"<<af_table[af_key_t(s, c)];
        std::cerr<<std::endl;
    }
    


    // compute super trees
    auto trees = supertrees(samples, af_clusters, af_table);
    if(trees.size() == 0) std::cerr<<"[warning] no solution found"<<std::endl;
    
    // reopen vcf file to produce output
    vcf.release();
    vcf = htsOpen(argv[1], "r");
    header = htsHeader<bcfHeader>::read(vcf);
   
    vcf_print(vcf, header, trees, samples, af_clusters, af_table);

    return 0;
}


