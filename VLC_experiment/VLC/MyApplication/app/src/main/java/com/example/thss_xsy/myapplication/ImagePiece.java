package com.example.thss_xsy.myapplication;

/**
 * Created by THSS-XSY on 2018/2/4.
 */
import android.graphics.Bitmap;

public class ImagePiece
{
    private Bitmap bitmap ;

    public ImagePiece(){
    }

    public ImagePiece(Bitmap bitmap){
        this.bitmap = bitmap;
    }

    public Bitmap getBitmap(){
        return bitmap;
    }

    public void setBitmap(Bitmap bitmap){
        this.bitmap = bitmap;
    }
}

