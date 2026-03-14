/*
 * Copyright (c) 2025 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#define RULEMAK_MODMORPH_ALTGR(behavior_name, binding_base, binding_alt, display_name) \
    / { \
        behaviors { \
            behavior_name: behavior_name { \
                compatible = "zmk,behavior-mod-morph"; \
                #binding-cells = <0>; \
                bindings = <binding_base>, <binding_alt>; \
                mods = <(MOD_RALT)>; \
                display-name = display_name; \
            }; \
        }; \
    };

#define RULEMAK_MODMORPH_FALLBACK(behavior_name, binding_key, binding_default) \
    / { \
        behaviors { \
            behavior_name: behavior_name { \
                compatible = "zmk,behavior-mod-morph"; \
                #binding-cells = <0>; \
                bindings = <binding_key>, <binding_default>; \
                mods = <(MOD_LCTL|MOD_RCTL|MOD_LALT|MOD_LGUI|MOD_RGUI)>; \
                keep-mods = <(MOD_LCTL|MOD_RCTL|MOD_LALT|MOD_LGUI|MOD_RGUI)>; \
                display-name = display_name; \
            }; \
        }; \
    };

#define RULEMAK_REMAP(name, fallback_key, base_key, alt_key) \
    RULEMAK_MODMORPH_ALTGR(ru_ ## replace_key ## _both, base_key, alt_key, "(internal) Rulemak replace_key") \
    RULEMAK_MODMORPH_FALLBACK(ru_ ## replace_key, &ru_ ## replace_key ## _both, &kp fallback_key, "Rulemak replace_key")

RULEMAK_REMAP(Q, Q, &kp Z, &none)
RULEMAK_REMAP(W, W, &kp LBKT, &kp O)
RULEMAK_REMAP(E, F, &kp A, &none)
RULEMAK_REMAP(R, P, &kp G, &none)
RULEMAK_REMAP(T, B, &kp COMMA, &none)
RULEMAK_REMAP(Y, J, &kp Q, &none)
RULEMAK_REMAP(U, L, &kp K, &none)
RULEMAK_REMAP(I, U, &kp E, &none)
RULEMAK_REMAP(O, Y, &kp S, &none)
RULEMAK_REMAP(P, SEMI, &kp SEMI, &kp SQT)
RULEMAK_REMAP(A, A, &kp F, &none)
RULEMAK_REMAP(S, R, &kp C, &none)
RULEMAK_REMAP(D, S, &kp L, &none)
RULEMAK_REMAP(F, T, &kp N, &none)
RULEMAK_REMAP(G, G, &kp U, &none)
RULEMAK_REMAP(H, M, &kp V, &none)
RULEMAK_REMAP(J, N, &kp Y, &none)
RULEMAK_REMAP(K, E, &kp T, &none)
RULEMAK_REMAP(L, I, &kp B, &kp GRAVE)
RULEMAK_REMAP(SEMI, O, &kp J, &none)
RULEMAK_REMAP(Z, Z, &kp P, &none)
RULEMAK_REMAP(X, X, &kp SEMI, &none)
RULEMAK_REMAP(C, C, &kp W, &kp O)
RULEMAK_REMAP(V, D, &kp L, &none)
RULEMAK_REMAP(B, V, &kp D, &none)
RULEMAK_REMAP(N, K, &kp R, &none)
RULEMAK_REMAP(M, H, &kp X, &none)
RULEMAK_REMAP(COMMA, COMMA, &kp DOT, &kp M)
RULEMAK_REMAP(DOT, DOT, &kp DOT, &kp RBKT)
RULEMAK_REMAP(SLASH, SLASH, &kp DOT)
