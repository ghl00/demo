#include "ObjectRepository.h"

using ObjectIdentifierMap = std::unordered_map<std::string, size_t>;


class ObjectRepository final : public IObjectRepository
{
private:
    ObjectIdentifierMap _newItemMap;

public:
    explicit ObjectRepository()
    {
    }

    ~ObjectRepository() final
    {
    }

    const ObjectRepositoryItem* FindObject(std::string_view identifier) const override final
    {
        auto kvp = _newItemMap.find(std::string(identifier));
        if (kvp != _newItemMap.end())
        {
            return &_items[kvp->second];
        }
        return nullptr;
    }
};

std::unique_ptr<IObjectRepository> CreateObjectRepository()
{
    return std::make_unique<ObjectRepository>();
}