package io.github.tum_gis.ecitygml

import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface CitygmlFormatLib: Library {
}
/** Encoding of CityGML content.
*/
enum class CitygmlFormat {
    Gml,
    GmlZst,
    GmlGz;

    fun toNative(): Int {
        return this.ordinal
    }


    companion object {
        internal val libClass: Class<CitygmlFormatLib> = CitygmlFormatLib::class.java
        internal val lib: CitygmlFormatLib = Native.load("ecitygml_ffi", libClass) 
        fun fromNative(native: Int): CitygmlFormat {
            return CitygmlFormat.entries[native]
        }

        fun default(): CitygmlFormat {
            return Gml
        }
    }
}
