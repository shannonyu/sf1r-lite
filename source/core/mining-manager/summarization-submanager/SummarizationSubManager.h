#ifndef SF1R_MINING_MANAGER_MULTI_DOC_SUMMARIZATION_SUBMANAGER_H
#define SF1R_MINING_MANAGER_MULTI_DOC_SUMMARIZATION_SUBMANAGER_H

#include "Summarization.h"

#include <configuration-manager/SummarizeConfig.h>
#include <query-manager/QueryTypeDef.h>

#include <3rdparty/am/stx/btree_map.h>
#include <queue>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

namespace idmlib
{
namespace util
{
class IDMAnalyzer;
}
}

namespace sf1r
{
class DocumentManager;
class IndexManager;
class ScdWriter;

class SummarizationStorage;
class CommentCacheStorage;
class Corpus;
class OpinionsManager;

class MultiDocSummarizationSubManager
{
public:
    MultiDocSummarizationSubManager(
            const std::string& homePath,
            SummarizeConfig schema,
            boost::shared_ptr<DocumentManager> document_manager,
            boost::shared_ptr<IndexManager> index_manager,
            idmlib::util::IDMAnalyzer* analyzer);

    ~MultiDocSummarizationSubManager();

    void EvaluateSummarization();

    void AppendSearchFilter(
            std::vector<QueryFiltering::FilteringType>& filtingList);

    bool GetSummarizationByRawKey(
            const izenelib::util::UString& rawKey,
            Summarization& result);

private:
    bool DoEvaluateSummarization_(
            Summarization& summarization,
            const KeyType& key,
            const CommentCacheItemType& comment_cache_item);

    void DoComputeOpinion(OpinionsManager* Op);

    void DoOpinionExtraction(
        Summarization& summarization,
        const KeyType& key,
        const CommentCacheItemType& comment_cache_item);

    void DoWriteOpinionResult();

    uint32_t GetLastDocid_() const;

    void SetLastDocid_(uint32_t docid) const;

private:
    std::string last_docid_path_;

    SummarizeConfig schema_;

    boost::shared_ptr<DocumentManager> document_manager_;
    boost::shared_ptr<IndexManager> index_manager_;
    boost::shared_ptr<ScdWriter> score_scd_writer_;
    boost::shared_ptr<ScdWriter> opinion_scd_writer_;

    idmlib::util::IDMAnalyzer* analyzer_;

    CommentCacheStorage* comment_cache_storage_;
    SummarizationStorage* summarization_storage_;

    Corpus* corpus_;
    std::vector<OpinionsManager*> Ops_;
    boost::mutex  waiting_opinion_lock_;
    boost::mutex  opinion_results_lock_;
    boost::condition_variable  waiting_opinion_cond_;
    boost::condition_variable  opinion_results_cond_;
    struct WaitingComputeCommentItem
    {
        KeyType key;
        CommentCacheItemType cached_comments;
        Summarization summarization;
    };
    struct OpinionResultItem
    {
        KeyType key;
        std::vector< std::pair<double, izenelib::util::UString> >  result_opinions;
        std::vector< std::pair<double, izenelib::util::UString> >  result_advantage;
        std::vector< std::pair<double, izenelib::util::UString> >  result_disadvantage;
        Summarization summarization;
    };
    std::queue< WaitingComputeCommentItem >  waiting_opinion_comments_;
    std::queue< OpinionResultItem >  opinion_results_;
    std::vector<boost::thread*>  opinion_compute_threads_;
    bool  can_quit_compute_;
};

}

#endif
