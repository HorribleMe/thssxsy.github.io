package com.example.thss_xsy.myapplication;


import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.view.View;
import android.view.View.OnClickListener;
import android.media.Image;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.content.Intent;
import android.widget.Toast;


public class MainActivity extends AppCompatActivity {
    private String TAG = "mainActivity";
    private ImageView picture;
    private String path;
    private EditText information;
    private Button getPicture;
    private Button startTrans;
    private Uri mImageCaptureUri;

    private static final String IMAGE_UNSPECIFIED = "image/*";
    public static final int REQUEST_CODE_SELECT_FROM_GALLERY = 1;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        picture = (ImageView)findViewById(R.id.picture);
        getPicture = (Button) findViewById(R.id.open);
        information = (EditText) findViewById(R.id.information);
        startTrans = (Button) findViewById(R.id.startTrans);

    }

    public void open(View v) {
        Intent intent = new Intent();
        intent.setType(IMAGE_UNSPECIFIED);
        intent.setAction(Intent.ACTION_GET_CONTENT);
        startActivityForResult(intent, REQUEST_CODE_SELECT_FROM_GALLERY);
    }


    public void startTrans(View v) {
        String data = information.getText().toString();
        Log.i(TAG, "startTransmission: " + data);
        if (path == null){
            Toast.makeText(getApplicationContext(), "Please choose image.", Toast.LENGTH_LONG).show();
            return;
        }
        Intent intent = new Intent();
        intent.setClass(this, Trans.class);
        Bundle n = new Bundle();
        n.putString("path", path);
        n.putString("data", data);
        intent.putExtras(n);
        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        this.startActivity(intent);
    }

    public void receive(View v) {
        Log.i(TAG, "startRead");
        if (path == null){
            Toast.makeText(getApplicationContext(), "Please choose image for reader.", Toast.LENGTH_LONG).show();
            return;
        }
        Intent intent = new Intent();
        intent.setClass(this, Reader.class);
        Bundle n = new Bundle();
        n.putString("path", path);
        intent.putExtras(n);
        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        this.startActivity(intent);
        int i = 1;
        i = i + 1;
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (resultCode != RESULT_OK)
            return;

        switch (requestCode) {
            case REQUEST_CODE_SELECT_FROM_GALLERY:
                Bitmap yourSelectedImage = null;
                mImageCaptureUri = data.getData();
                String[] filePathColumn = {MediaStore.Images.Media.DATA};

                Cursor cursor = getContentResolver().query(mImageCaptureUri, filePathColumn, null, null, null);
                cursor.moveToFirst();

                int columnIndex = cursor.getColumnIndex(filePathColumn[0]);
                path = cursor.getString(columnIndex);
                cursor.close();
                yourSelectedImage = BitmapFactory.decodeFile(path);

                picture.setImageBitmap(yourSelectedImage);
                break;
        }
    }

}
