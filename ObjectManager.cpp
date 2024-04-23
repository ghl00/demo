#include "ObjectManager.h"
#include "ObjectRepository.h"
#include "Object.h"


class ObjectManager final : public IObjectManager
{
private:
    IObjectRepository& _objectRepository;

public:
    explicit ObjectManager(IObjectRepository& objectRepository)
        : _objectRepository(objectRepository)
    {
    }

    Object* LoadObject(std::string_view identifier) override
    {
        const ObjectRepositoryItem* ori = _objectRepository.FindObject(identifier);
        return RepositoryItemToObject(ori);
    }
};

std::unique_ptr<IObjectManager> CreateObjectManager(IObjectRepository& objectRepository)
{
    return std::make_unique<ObjectManager>(objectRepository);
}