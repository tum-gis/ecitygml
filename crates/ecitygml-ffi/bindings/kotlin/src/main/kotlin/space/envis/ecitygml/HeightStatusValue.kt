package space.envis.ecitygml

import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface HeightStatusValueLib: Library {
}
/** Whether a height was estimated or measured.
*/
enum class HeightStatusValue {
    Estimated,
    Measured;

    fun toNative(): Int {
        return this.ordinal
    }


    companion object {
        internal val libClass: Class<HeightStatusValueLib> = HeightStatusValueLib::class.java
        internal val lib: HeightStatusValueLib = Native.load("ecitygml_ffi", libClass) 
        fun fromNative(native: Int): HeightStatusValue {
            return HeightStatusValue.entries[native]
        }

        fun default(): HeightStatusValue {
            return Estimated
        }
    }
}
