#ifndef PushTheBox_ResourceManagement_MeshResourceLoader_h
#define PushTheBox_ResourceManagement_MeshResourceLoader_h

#include <Corrade/Containers/ArrayView.h>
#include <Corrade/Utility/Configuration.h>
#include <Magnum/AbstractResourceLoader.h>

#include "PushTheBox.h"

namespace PushTheBox { namespace ResourceManagement {

#ifndef DOXYGEN_GENERATING_OUTPUT
namespace Implementation {
    struct ResourceKeyHash {
        inline std::size_t operator()(ResourceKey key) const {
            return *reinterpret_cast<const std::size_t*>(key.byteArray());
        }
    };
}
#endif

class MeshResourceLoader: public AbstractResourceLoader<Mesh> {
    public:
        MeshResourceLoader();

        std::string name(ResourceKey key) const;


    private:
        void doLoad(ResourceKey key) override;

        std::unordered_map<ResourceKey, std::uint32_t, Implementation::ResourceKeyHash> nameMap;

        Utility::Configuration* conf;
        Containers::ArrayView<const char> data;
};

}}

#endif
