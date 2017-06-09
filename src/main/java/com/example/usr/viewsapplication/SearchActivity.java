package com.example.usr.viewsapplication;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageButton;

public class SearchActivity extends AppCompatActivity implements View.OnClickListener {

    private EditText et_search;
    private ImageButton search_btn;
    private ImageButton clear_btn;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_search);

        et_search = (EditText) findViewById(R.id.et_search);

        search_btn = (ImageButton) findViewById(R.id.search_btn);
        search_btn.setOnClickListener(this);

        clear_btn = (ImageButton) findViewById(R.id.clear_btn);
        clear_btn.setOnClickListener(this);
    }



    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.search_btn:
                Bundle bundle = new Bundle();
                bundle.putString(Const.SEARCH_TEXT, et_search.getText().toString());
                SearchTimeLineFragment searchTimeLineFragment = new SearchTimeLineFragment();
                searchTimeLineFragment.setArguments(bundle);
                getSupportFragmentManager()
                        .beginTransaction()
                        .replace(R.id.search_timeline, searchTimeLineFragment)
                        .commit();
                break;
            case R.id.clear_btn:
                et_search.setText("");
                break;
        }

    }
}
