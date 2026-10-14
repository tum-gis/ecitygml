package io.github.tum_gis.ecitygml

import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface GranularityValueLib: Library {
}
/** Level of subdivision of a transportation space (lane or way).
*/
enum class GranularityValue {
    Lane,
    Way;

    fun toNative(): Int {
        return this.ordinal
    }


    companion object {
        internal val libClass: Class<GranularityValueLib> = GranularityValueLib::class.java
        internal val lib: GranularityValueLib = Native.load("ecitygml_ffi", libClass) 
        fun fromNative(native: Int): GranularityValue {
            return GranularityValue.entries[native]
        }

        fun default(): GranularityValue {
            return Lane
        }
    }
}
