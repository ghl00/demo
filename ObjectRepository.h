#pragma once
#include "demo.h"

struct IObjectRepository
{
    virtual ~IObjectRepository() = default;

    virtual const ObjectRepositoryItem* FindObject(std::string_view identifier) const = 0;
};

std::unique_ptr<IObjectRepository> CreateObjectRepository();