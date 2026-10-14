package io.github.tum_gis.ecitygml

import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface SpaceTypeLib: Library {
}
/** Whether a space is closed, open or semi-open.
*/
enum class SpaceType {
    Closed,
    Open,
    SemiOpen;

    fun toNative(): Int {
        return this.ordinal
    }


    companion object {
        internal val libClass: Class<SpaceTypeLib> = SpaceTypeLib::class.java
        internal val lib: SpaceTypeLib = Native.load("ecitygml_ffi", libClass) 
        fun fromNative(native: Int): SpaceType {
            return SpaceType.entries[native]
        }

        fun default(): SpaceType {
            return Closed
        }
    }
}
