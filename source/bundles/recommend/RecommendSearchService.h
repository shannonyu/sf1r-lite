/**
 * @file RecommendSearchService.h
 * @author Jun Jiang
 * @date 2011-04-20
 */

#ifndef RECOMMEND_SEARCH_SERVICE_H
#define RECOMMEND_SEARCH_SERVICE_H

#include <recommend-manager/RecTypes.h>
#include <recommend-manager/Item.h>
#include <recommend-manager/RecommendItem.h>

#include <util/osgi/IService.h>

#include <string>
#include <vector>

namespace sf1r
{
class User;
class UserManager;
class ItemManager;
class RecommenderFactory;
struct RecommendParam;
struct TIBParam;
struct ItemBundle;

class RecommendSearchService : public ::izenelib::osgi::IService
{
public:
    RecommendSearchService(
        UserManager* userManager,
        ItemManager* itemManager,
        RecommenderFactory* recommenderFactory,
        RecIdGenerator* userIdGenerator,
        RecIdGenerator* itemIdGenerator
    );

    bool getUser(const std::string& userIdStr, User& user);

    bool getItem(const std::string& itemIdStr, Item& item);

    bool recommend(
        RecommendParam& param,
        std::vector<RecommendItem>& recItemVec
    );

    bool topItemBundle(
        const TIBParam& param,
        std::vector<ItemBundle>& bundleVec
    );

private:
    bool convertIds_(RecommendParam& param);
    bool convertItemId_(
        const std::vector<std::string>& inputItemVec,
        std::vector<itemid_t>& outputItemVec
    );
    bool getRecommendItems_(std::vector<RecommendItem>& recItemVec) const;
    bool getBundleItems_(std::vector<ItemBundle>& bundleVec) const;

private:
    UserManager* userManager_;
    ItemManager* itemManager_;
    RecommenderFactory* recommenderFactory_;
    RecIdGenerator* userIdGenerator_;
    RecIdGenerator* itemIdGenerator_;
};

} // namespace sf1r

#endif // RECOMMEND_SEARCH_SERVICE_H
