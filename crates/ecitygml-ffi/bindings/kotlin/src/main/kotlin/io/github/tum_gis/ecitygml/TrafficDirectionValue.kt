package io.github.tum_gis.ecitygml

import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface TrafficDirectionValueLib: Library {
}
/** Allowed traffic direction of a traffic space.
*/
enum class TrafficDirectionValue {
    Forwards,
    Backwards,
    Both;

    fun toNative(): Int {
        return this.ordinal
    }


    companion object {
        internal val libClass: Class<TrafficDirectionValueLib> = TrafficDirectionValueLib::class.java
        internal val lib: TrafficDirectionValueLib = Native.load("ecitygml_ffi", libClass) 
        fun fromNative(native: Int): TrafficDirectionValue {
            return TrafficDirectionValue.entries[native]
        }

        fun default(): TrafficDirectionValue {
            return Forwards
        }
    }
}
