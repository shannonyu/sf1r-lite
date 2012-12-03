#include "NaiveTopicDetector.hpp"
#include <glog/logging.h>
#include <icma/icma.h>
#include <la-manager/LAPool.h>

#include <boost/filesystem.hpp>

namespace sf1r
{
using namespace cma;
NaiveTopicDetector::NaiveTopicDetector(const std::string& dict_path)
    :tokenize_dicpath_(dict_path)
    ,analyzer_(NULL)
    ,knowledge_(NULL)
{
    InitCMA_();
}

NaiveTopicDetector::~NaiveTopicDetector()
{
    if (analyzer_) delete analyzer_;
    if (knowledge_) delete knowledge_;
}

bool NaiveTopicDetector::GetTopics(const std::string& content, std::vector<std::string>& topic_list, size_t limit)
{
    if(!analyzer_) return false;
    Sentence pattern_sentence(content.c_str());
    analyzer_->runWithSentence(pattern_sentence);
    LOG(INFO) << "query tokenize by maxprefix match in dictionary: ";
    for (int i = 0; i < pattern_sentence.getCount(0); i++)
    {
        std::cout<<"topic "<<pattern_sentence.getLexicon(0, i)<<std::endl;
        std::string topic(pattern_sentence.getLexicon(0, i));
        if(topic.length() > 1)
            topic_list.push_back(topic);
    }
    cout << endl;	
    if(limit > 0 && limit > topic_list.size())
        topic_list.resize(limit);
    return true;
}

void NaiveTopicDetector::InitCMA_()
{
    std::string cma_path;
    LAPool::getInstance()->get_cma_path(cma_path);
    boost::filesystem::path cma_tdt_dic(cma_path);
    cma_tdt_dic /= boost::filesystem::path(tokenize_dicpath_);
    LOG(INFO) << "topic detector dictionary path : " << cma_tdt_dic.c_str() << endl;
    knowledge_ = CMA_Factory::instance()->createKnowledge();
    knowledge_->loadModel( "utf8", cma_tdt_dic.c_str(), false);
    analyzer_ = CMA_Factory::instance()->createAnalyzer();
    analyzer_->setOption(Analyzer::OPTION_TYPE_POS_TAGGING, 0);
    // using the maxprefix analyzer
    analyzer_->setOption(Analyzer::OPTION_ANALYSIS_TYPE, 100);
    analyzer_->setKnowledge(knowledge_);
    LOG(INFO) << "load dictionary for topic detector knowledge finished." << endl;
}

}
