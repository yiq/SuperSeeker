#ifndef VCF_PRINT_H
#define VCF_PRINT_H

#include <htslibpp.h>
#include <htslibpp_variant.h>
#include "typedefs.h"

using namespace YiCppLib::HTSLibpp;

void vcf_print(YiCppLib::HTSLibpp::htsFile& vcf,
        YiCppLib::HTSLibpp::bcfHeader& header,
        const solution_t& solutions,
        const std::vector<std::string>& samples,
        const std::set<std::string>& af_clusters,
        const af_table_t& af_table);

#endif
