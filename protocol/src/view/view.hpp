#ifndef SDC_VIEW_VIEW_HPP
#define SDC_VIEW_VIEW_HPP

namespace sdc {
namespace view {

struct View {
    constexpr View() = default;
    View(View const &) = delete;
};

} // namespace view
} // namespace sdc

#endif // SDC_VIEW_VIEW_HPP
