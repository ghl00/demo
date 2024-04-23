#pragma once
#include "demo.h"
#include "ObjectRepository.h"

struct IObjectManager
{
    virtual ~IObjectManager() = default;

    virtual Object* LoadObject(std::string_view identifier) = 0;
};



std::unique_ptr<IObjectManager> CreateObjectManager(IObjectRepository& objectRepository);
