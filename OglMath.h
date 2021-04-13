#pragma once

struct Vector3{
    float x, y, z;
};

/*float* HexToFv(const char* color)
{
    float *hex = new float[4];

    return hex;
}*/

/*struct Vec4
{
    float x, y, z, w;

    float* GetPointer()
    {
        float *arr = new float[] {x, y, z, w};
        return arr;
    }
};


struct Mat4f
{
    Vec4 x, y, z, w;

    float* GetPointer()
    {
        float *arr = new float[] {x.x, x.y, x.z, x.w, y.x, y.y, y.z, y.w, z.x, z.y, z.z, z.w, w.x, w.y, w.z, w.w};
        return arr;
    }
};

Mat4f CreateOrthoMatrix(float left, float right, float bottom, float top, float n, float f)
{
    Vec4 x = {2/(right-left), 0, 0, -((right+left)/(right-left))};
    Vec4 y = {0, 2/(top-bottom), 0, -((top+bottom)/(top-bottom))};
    Vec4 z = {0, 0, -2/(f-n), -((f+n)/(f-n))};
    Vec4 w = {0, 0, 0, 1};

    Mat4f mat = {x,y,z,w};

    return mat;
}*/
