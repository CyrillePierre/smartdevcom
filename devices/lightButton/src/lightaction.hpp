#ifndef SDC_LIGHTACTION_HPP
#define SDC_LIGHTACTION_HPP

#include "types.hpp"
#include "action.hpp"
#include "lightbutton.hpp"
#include "dynamicbitset.hpp"

namespace sdc {

class LightAction : public sdc::Action {
    static constexpr type::Word actionType = 0x1211;
    static constexpr type::Byte const proto[] = {
        static_cast<type::Byte>(actionType >> 8),
        static_cast<type::Byte>(actionType),
        0x01, ParamType::BOOL, 0x00
    };
    static constexpr auto protoSize = sizeof(proto);

    LightButton & _light;

public:
    LightAction(LightButton & lb)
        : Action(actionType, protoSize, proto[protoSize - 1]), _light{lb} {}

    virtual ~LightAction() {}

    virtual void operator ()(net::NetStream &);

    virtual void pushPrototype(DynamicBitset & db)
    { db.push(proto, protoSize); }
};


} // namespace sdc

#endif // SDC_LIGHTACTION_HPP
