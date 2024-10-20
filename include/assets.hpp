#pragma once

#include <string_view>
#include "beatsaber-hook/shared/utils/typedefs.h"

// This is a cmake generated header to include my png and bsml files

struct IncludedAsset {

    IncludedAsset(uint8_t* start, uint8_t* end) : array(reinterpret_cast<Array<uint8_t>*>(start)) {
        array->klass = nullptr;
        array->monitor = nullptr;
        array->bounds = nullptr;
        array->max_length = end - start - 33;
        *(end - 1)= '\0';
    }
    
    operator ArrayW<uint8_t>() const {
        init();
        return array;
    }

    operator std::string_view() const {
        return { reinterpret_cast<char*>(array->_values), array->get_Length() };
    }
    
    operator std::span<uint8_t>() const {
        return { array->_values, array->get_Length() };
    }

    void init() const {
        if(!array->klass)
            array->klass = classof(Array<uint8_t>*);
    }

    private:
        Array<uint8_t>* array;

};

#define DECLARE_FILE(name)                         \
    extern "C" uint8_t _binary_##name##_start[];  \
    extern "C" uint8_t _binary_##name##_end[];    \
    const IncludedAsset name { _binary_##name##_start, _binary_##name##_end};

namespace IncludedAssets {

	DECLARE_FILE(GridDotsScreen_bsml)
	DECLARE_FILE(GridInfoUI_bsml)
	DECLARE_FILE(NoteInfoUI_bsml)
	DECLARE_FILE(NoteUIModal_bsml)
	DECLARE_FILE(PanelScreen_bsml)
	DECLARE_FILE(SettingsUI_bsml)
	DECLARE_FILE(StatsPanel_bsml)
	DECLARE_FILE(arrow_png)
	DECLARE_FILE(bloq_png)
	DECLARE_FILE(bloq_gradient_png)
	DECLARE_FILE(border_png)
	DECLARE_FILE(cut_arrow_png)
	DECLARE_FILE(dot_png)

}
