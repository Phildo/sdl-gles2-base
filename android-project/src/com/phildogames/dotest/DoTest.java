package com.phildogames.dotest;

import java.util.*;
import java.net.*;

import android.util.*;
import android.app.*;
import android.content.*;
import android.view.*;
import android.widget.*;
import android.os.*;
import android.graphics.*;
import android.media.*;
import android.hardware.*;

import org.libsdl.app.SDLActivity;

public class DoTest extends SDLActivity
{
  private static Context context;

  @Override
    public void onCreate(Bundle savedInstanceState)
    {
      super.onCreate(savedInstanceState);
      context = getApplicationContext();
      getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
    }
}

/*
//Minimal activity

package com.phildogames.dotest;
import org.libsdl.app.SDLActivity;·
public class DoTest extends SDLActivity { }
*/

