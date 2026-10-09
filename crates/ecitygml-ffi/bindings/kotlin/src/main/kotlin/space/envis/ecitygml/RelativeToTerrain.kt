package space.envis.ecitygml

import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface RelativeToTerrainLib: Library {
}
/** Position of a city object relative to the terrain.
*/
enum class RelativeToTerrain {
    EntirelyAboveTerrain,
    SubstantiallyAboveTerrain,
    SubstantiallyAboveAndBelowTerrain,
    SubstantiallyBelowTerrain,
    EntirelyBelowTerrain;

    fun toNative(): Int {
        return this.ordinal
    }


    companion object {
        internal val libClass: Class<RelativeToTerrainLib> = RelativeToTerrainLib::class.java
        internal val lib: RelativeToTerrainLib = Native.load("ecitygml_ffi", libClass) 
        fun fromNative(native: Int): RelativeToTerrain {
            return RelativeToTerrain.entries[native]
        }

        fun default(): RelativeToTerrain {
            return EntirelyAboveTerrain
        }
    }
}
