package io.github.tum_gis.ecitygml

import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface LevelOfDetailLib: Library {
    fun ecitygml_LevelOfDetail_as_index(inner: Int): FFISizet
    fun ecitygml_LevelOfDetail_try_from(value: FFIUint8): ResultIntPointer
}
/** A CityGML level of detail (LoD 0 to 3).
*/
enum class LevelOfDetail {
    Zero,
    One,
    Two,
    Three;

    fun toNative(): Int {
        return this.ordinal
    }


    companion object {
        internal val libClass: Class<LevelOfDetailLib> = LevelOfDetailLib::class.java
        internal val lib: LevelOfDetailLib = Native.load("ecitygml_ffi", libClass) 
        fun fromNative(native: Int): LevelOfDetail {
            return LevelOfDetail.entries[native]
        }

        fun default(): LevelOfDetail {
            return Zero
        }
        @JvmStatic
        
        /** The level with that number; fails with `InvalidArgument` above 3 (Rust: `TryFrom<u8>`).
        */
        fun tryFrom(value: UByte): Result<LevelOfDetail> {
            
            val returnVal = lib.ecitygml_LevelOfDetail_try_from(FFIUint8(value));
            val nativeOkVal = returnVal.getNativeOk();
            if (nativeOkVal != null) {
                return (LevelOfDetail.fromNative(nativeOkVal)).ok()
            } else {
                val selfEdges: List<Any> = listOf()
                val handle = returnVal.getNativeErr()!! 
                val returnOpaque = Error(handle, selfEdges, true)
                return returnOpaque.err()
            }
        }
    }
    
    /** The level as a number, e.g. 2 for `Two`.
    */
    fun asIndex(): ULong {
        
        val returnVal = lib.ecitygml_LevelOfDetail_as_index(this.toNative());
        return (returnVal.toULong())
    }
}
