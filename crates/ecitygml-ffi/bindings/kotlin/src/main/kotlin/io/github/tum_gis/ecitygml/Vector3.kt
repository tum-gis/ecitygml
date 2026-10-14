package io.github.tum_gis.ecitygml

import com.sun.jna.Callback
import com.sun.jna.Library
import com.sun.jna.Native
import com.sun.jna.Pointer
import com.sun.jna.Structure

internal interface Vector3Lib: Library {
}

internal class Vector3Native: Structure(), Structure.ByValue {
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




internal class OptionVector3Native constructor(): Structure(), Structure.ByValue {
    @JvmField
    internal var value: Vector3Native = Vector3Native()

    @JvmField
    internal var isOk: Byte = 0

    // Define the fields of the struct
    override fun getFieldOrder(): List<String> {
        return listOf("value", "isOk")
    }

    internal fun option(): Vector3Native? {
        if (isOk == 1.toByte()) {
            return value
        } else {
            return null
        }
    }


    constructor(value: Vector3Native, isOk: Byte): this() {
        this.value = value
        this.isOk = isOk
    }

    companion object {
        internal fun some(value: Vector3Native): OptionVector3Native {
            return OptionVector3Native(value, 1)
        }

        internal fun none(): OptionVector3Native {
            return OptionVector3Native(Vector3Native(), 0)
        }
    }

}

/** A 3D vector, passed by value (e.g. the translation of `CityModel::apply_translation`).
*/
class Vector3 (var x: Double, var y: Double, var z: Double) {
    companion object {

        internal val libClass: Class<Vector3Lib> = Vector3Lib::class.java
        internal val lib: Vector3Lib = Native.load("ecitygml_ffi", libClass)
        val NATIVESIZE: Long = Native.getNativeSize(Vector3Native::class.java).toLong()

        internal fun fromNative(nativeStruct: Vector3Native): Vector3 {
            val x: Double = nativeStruct.x
            val y: Double = nativeStruct.y
            val z: Double = nativeStruct.z

            return Vector3(x, y, z)
        }

    }
    internal fun toNative(): Vector3Native {
        var native = Vector3Native()
        native.x = this.x
        native.y = this.y
        native.z = this.z
        return native
    }

}