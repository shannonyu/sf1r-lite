#include "ProductScoreTable.h"
#include "../util/fcontainer_febird.h"

using namespace sf1r;

namespace
{
const char* FILE_NAME_SUFFIX = ".bin";
}

ProductScoreTable::ProductScoreTable()
{
}

ProductScoreTable::ProductScoreTable(
    const std::string& dirPath,
    const std::string& scoreTypeName)
    : dirPath_(dirPath)
    , scoreTypeName_(scoreTypeName)
{
}

ProductScoreTable& ProductScoreTable::operator=(const ProductScoreTable& other)
{
    if (this != &other)
    {
        ScopedWriteLock lock(mutex_);
        ScopedReadLock otherLock(other.mutex_);

        dirPath_ = other.dirPath_;
        scoreTypeName_ = other.scoreTypeName_;
        scores_ = other.scores_;
    }

    return *this;
}

void ProductScoreTable::swap(ProductScoreTable& other)
{
    if (this == &other)
        return;

    ScopedWriteLock lock(mutex_);
    ScopedWriteLock otherLock(other.mutex_);

    dirPath_.swap(other.dirPath_);
    scoreTypeName_.swap(other.scoreTypeName_);
    scores_.swap(other.scores_);
}

bool ProductScoreTable::open()
{
    ScopedWriteLock lock(mutex_);

    return load_container_febird(dirPath_,
                                 scoreTypeName_ + FILE_NAME_SUFFIX,
                                 scores_);
}

bool ProductScoreTable::flush()
{
    ScopedReadLock lock(mutex_);

    return save_container_febird(dirPath_,
                                 scoreTypeName_ + FILE_NAME_SUFFIX,
                                 scores_);
}

void ProductScoreTable::resize(std::size_t num)
{
    ScopedWriteLock lock(mutex_);

    scores_.resize(num, 0);
}

void ProductScoreTable::setScore(docid_t docId, score_t score)
{
    //ScopedWriteLock lock(mutex_);

    scores_[docId] = score;
}

score_t ProductScoreTable::getScoreHasLock(docid_t docId) const
{
    ScopedReadLock lock(mutex_);

    return getScoreNoLock(docId);
}

score_t ProductScoreTable::getScoreNoLock(docid_t docId) const
{
    if (docId < scores_.size())
        return scores_[docId];

    return 0;
}
