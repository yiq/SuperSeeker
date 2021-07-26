#include "vcf_print.h"
#include "supertree.h"
#include <algorithm>
#include <sstream>
#include <iostream>
#include <htslib/vcf.h>

std::ostream& operator<<(std::ostream& os, const edge_t& edge) {
    os <<edge.first << "->" << edge.second;
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::pair<std::string, float>& af) {
    os<<af.first<<":"<<af.second;
    return os;
}

template<typename InputIt>
std::string join(InputIt begin,
                 InputIt end,
                 const std::string & separator =", ",
                 const std::string & concluder ="")
{
    std::ostringstream ss;

    if(begin != end) ss << *begin++;

    while(begin != end) {
        ss << separator;
        ss << *begin++;
    }

    ss << concluder;
    return ss.str();
}

void vcf_print(YiCppLib::HTSLibpp::htsFile& vcf,
        YiCppLib::HTSLibpp::bcfHeader& header,
        const solution_t& solutions,
        const std::vector<std::string>& samples,
        const std::set<std::string>& af_clusters,
        const af_table_t& af_table) {

    auto htsOutHandle = htsOpen("-", "w");

    auto outHeader = bcfHeader{bcf_hdr_dup(header.get())};

    for(auto& tree : solutions) {
        auto edge_str = join(tree.begin(), tree.end());
        std::ostringstream header_stream;
        header_stream << "##subclone=\"" + edge_str + "\"";
        header_stream << "; trace=<";

        std::vector<std::string> trace_strs;

        // per sample trace
        for(auto& sample : samples) {
            auto trace = supertree_trace(tree, sample, af_clusters, af_table);
            std::for_each(trace.begin(), trace.end(), [](auto &pair){pair.second *= 2;});
            auto trace_str = join(trace.begin(), trace.end());
            trace_strs.push_back(sample+"=\"" + trace_str + "\"");
        }

        header_stream << join(trace_strs.begin(), trace_strs.end());
        header_stream << ">";

        bcf_hdr_append( outHeader.get(), header_stream.str().c_str());
    }


    htsOutHandle<<outHeader;

    std::for_each(begin(vcf, header), end(vcf, header), [&](const auto& rec){
            htsOutHandle<<bcfHdrRecPair(outHeader, rec);
            });
}

