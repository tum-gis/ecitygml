package io.github.tum_gis.ecitygml

import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface Scale3Lib: Library {
}

internal class Scale3Native: Structure(), Structure.ByValue {
    @JvmField
    internal var x: Double = 0.0;
    @JvmField
    internal var y: Double = 0.0;
    @JvmField
    internal var z: Double = 0.0;

    // Define the fields of the struct
    override fun getFieldOrder(): List<String> {
        return listOf("x", "y", "z")
    }
}




internal class OptionScale3Native constructor(): Structure(), Structure.ByValue {
    @JvmField
    internal var value: Scale3Native = Scale3Native()

    @JvmField
    internal var isOk: Byte = 0

    // Define the fields of the struct
    override fun getFieldOrder(): List<String> {
        return listOf("value", "isOk")
    }

    internal fun option(): Scale3Native? {
        if (isOk == 1.toByte()) {
            return value
        } else {
            return null
        }
    }


    constructor(value: Scale3Native, isOk: Byte): this() {
        this.value = value
        this.isOk = isOk
    }

    companion object {
        internal fun some(value: Scale3Native): OptionScale3Native {
            return OptionScale3Native(value, 1)
        }

        internal fun none(): OptionScale3Native {
            return OptionScale3Native(Scale3Native(), 0)
        }
    }

}

/** A scale factor per axis, passed by value (the argument of `CityModel::apply_scale`).
*/
class Scale3 (var x: Double, var y: Double, var z: Double) {
    companion object {

        internal val libClass: Class<Scale3Lib> = Scale3Lib::class.java
        internal val lib: Scale3Lib = Native.load("ecitygml_ffi", libClass)
        val NATIVESIZE: Long = Native.getNativeSize(Scale3Native::class.java).toLong()

        internal fun fromNative(nativeStruct: Scale3Native): Scale3 {
            val x: Double = nativeStruct.x
            val y: Double = nativeStruct.y
            val z: Double = nativeStruct.z

            return Scale3(x, y, z)
        }

    }
    internal fun toNative(): Scale3Native {
        var native = Scale3Native()
        native.x = this.x
        native.y = this.y
        native.z = this.z
        return native
    }

}