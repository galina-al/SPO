package com.example.usr.viewsapplication;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.Toast;

import com.twitter.sdk.android.Twitter;
import com.twitter.sdk.android.core.Callback;
import com.twitter.sdk.android.core.Result;
import com.twitter.sdk.android.core.TwitterException;
import com.twitter.sdk.android.core.TwitterSession;
import com.twitter.sdk.android.core.identity.TwitterLoginButton;
import com.twitter.sdk.android.core.models.User;

import retrofit2.Call;


public class LoginActivity extends AppCompatActivity {

    private TwitterLoginButton loginButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);


        loginButton = (TwitterLoginButton) findViewById(R.id.twitter_login_button);
        loginButton.setCallback(new Callback<TwitterSession>() {
            @Override
            public void success(Result<TwitterSession> result) {
                TwitterSession session = result.data;
                String msg = "@" + session.getUserName() + " logged in!" ;
                Toast.makeText(getApplicationContext(), msg, Toast.LENGTH_LONG).show();

                Call<User> user = Twitter.getApiClient(session).getAccountService().verifyCredentials(true, false);
                user.enqueue(new Callback<User>() {
                    @Override
                    public void success(Result<User> result) {
                        putInfo(result);
                    }

                    @Override
                    public void failure(TwitterException exception) {
                        Log.d("TwitterKit", "Login with Twitter failure", exception);
                    }
                });

            }

            @Override
            public void failure(TwitterException exception) {
                Log.d("TwitterKit", "Login with Twitter failure", exception);
            }
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        loginButton.onActivityResult(requestCode, resultCode, data);
    }

    public void putInfo(Result<User> result){
        Intent intent = new Intent(LoginActivity.this, MainActivity.class);
        User userInfo = result.data;

        intent.putExtra(Const.USER_NAME, userInfo.name );
        intent.putExtra(Const.SCREEN_NAME, userInfo.screenName);
        intent.putExtra(Const.LOCATION, userInfo.location);
        intent.putExtra(Const.FOLLOWING_COUNT, String.valueOf(userInfo.friendsCount));
        intent.putExtra(Const.FOLLOWERS_COUNT, String.valueOf(userInfo.followersCount));
        intent.putExtra(Const.TWEET_COUNT, String.valueOf(userInfo.statusesCount));
        intent.putExtra(Const.PROFILE_IMG_URL, userInfo.profileImageUrl.replace("", ""));
        intent.putExtra(Const.PROFILE_IMG_BG_URL, userInfo.profileBannerUrl.replace("", ""));

        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_CLEAR_TASK);
        startActivity(intent);
    }
}
