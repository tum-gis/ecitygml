package space.envis.ecitygml

import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface RelativeToWaterLib: Library {
}
/** Position of a city object relative to the water surface.
*/
enum class RelativeToWater {
    EntirelyAboveWaterSurface,
    SubstantiallyAboveWaterSurface,
    SubstantiallyAboveAndBelowWaterSurface,
    SubstantiallyBelowWaterSurface,
    EntirelyBelowWaterSurface,
    TemporarilyAboveAndBelowWaterSurface;

    fun toNative(): Int {
        return this.ordinal
    }


    companion object {
        internal val libClass: Class<RelativeToWaterLib> = RelativeToWaterLib::class.java
        internal val lib: RelativeToWaterLib = Native.load("ecitygml_ffi", libClass) 
        fun fromNative(native: Int): RelativeToWater {
            return RelativeToWater.entries[native]
        }

        fun default(): RelativeToWater {
            return EntirelyAboveWaterSurface
        }
    }
}
