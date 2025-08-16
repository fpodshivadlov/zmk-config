#if !defined UC_LEAD
    #define UC_LEAD &macro_press &kp LALT &macro_tap &kp KP_PLUS
#endif
#if !defined UC_TRAIL
    #define UC_TRAIL &macro_release &kp LALT
#endif

#define UC_Cyrillic_Capital_Letter_A &kp N0 &kp N4 &kp N1 &kp N0
#define UC_Cyrillic_Small_Letter_A &kp N0 &kp N4 &kp N3 &kp N0

#define UC_Cyrillic_Capital_Letter_Yeru &kp N0 &kp N4 &kp N2 &kp B
#define UC_Cyrillic_Small_Letter_Yeru &kp N0 &kp N4 &kp N4 &kp B

#define UC_Cyrillic_Capital_Letter_Yi &kp N0 &kp N4 &kp N0 &kp N7
#define UC_Cyrillic_Small_Letter_Yi &kp N0 &kp N4 &kp N5 &kp N7

#define UC_MACRO(name, unicode) \
    / { \
        macros { \
            name: name { \
                compatible = "zmk,behavior-macro"; \
                wait-ms = <0>; \
                tap-ms = <0>; \
                #binding-cells = <0>; \
                bindings = <UC_LEAD>, <&macro_tap unicode>, <UC_TRAIL>; \
            }; \
        }; \
    };

#define UC_MODMORPH_FALLBACK(name, binding_key, binding_default) \
    / { \
        behaviors { \
            name: name { \
                compatible = "zmk,behavior-mod-morph"; \
                #binding-cells = <0>; \
                bindings = <binding_key>, <binding_default>; \
                mods = <(MOD_LCTL|MOD_RCTL|MOD_LALT|MOD_LGUI|MOD_RGUI)>; \
                keep-mods = <(MOD_LCTL|MOD_RCTL|MOD_LALT|MOD_LGUI|MOD_RGUI)>; \
            }; \
        }; \
    };

#define UC_MODMORPH_ALTGR(name, binding_base, binding_alt) \
    / { \
        behaviors { \
            name: name { \
                compatible = "zmk,behavior-mod-morph"; \
                #binding-cells = <0>; \
                bindings = <binding_base>, <binding_alt>; \
                mods = <(MOD_RALT)>; \
            }; \
        }; \
    };

#define UC_MODMORPH_SFT(name, binding_lower, binding_upper) \
    / { \
        behaviors { \
            name: name { \
                compatible = "zmk,behavior-mod-morph"; \
                #binding-cells = <0>; \
                bindings = <binding_lower>, <binding_upper>; \
                mods = <(MOD_LSFT|MOD_RSFT)>; \
            }; \
        }; \
    };

#define UC2(name, fallback_key, base_lower, base_upper) \
    UC_MACRO(name ## _base_lower, base_lower) \
    UC_MACRO(name ## _base_upper, base_upper) \
    UC_MODMORPH_SFT(name ## _base, &name ## _base_lower, &name ## _base_upper) \
    UC_MODMORPH_FALLBACK(name, &name ## _base, &kp fallback_key)

#define UC4(name, fallback_key, base_lower, base_upper, alt_lower, alt_upper) \
    UC_MACRO(name ## _base_lower, base_lower) \
    UC_MACRO(name ## _base_upper, base_upper) \
    UC_MACRO(name ## _alt_lower, alt_lower) \
    UC_MACRO(name ## _alt_upper, alt_upper) \
    UC_MODMORPH_SFT(name ## _base, &name ## _base_lower, &name ## _base_upper) \
    UC_MODMORPH_SFT(name ## _alt, &name ## _alt_lower, &name ## _alt_upper) \
    UC_MODMORPH_ALTGR(name ## _both, &name ## _base, &name ## _alt) \
    UC_MODMORPH_FALLBACK(name, &name ## _both, &kp fallback_key)
