
var audio_interval = 10000; //milliseconds
g_parameter = -99;

// Code For long Press
var timer;
var istrue = false;
var delay = 3000; // how much long u have to hold click in MS

// End Long press code

$(document).ready(function(){

    //need topics to start face detection confirmation and also to listen for navigation finish.
    console.log("document is ready");

    ros = new ROSLIB.Ros({
        /*change- replace 192.168.0.100 with your ROS Server's IP Address.
        9090 is default port number of rosbridge. */
        url : 'ws://localhost:9090'
    });

  /*  ros.on('connection', function() {
       alert("Congrats ! You are connected to ROS !")
    });   */

    /* Creating Topics
    --------------------*/
      ui_nav = new ROSLIB.Topic({
        ros : ros,
        name : '/ui_nav',
        messageType : 'std_msgs/Int32'
      });

      ui_guide = new ROSLIB.Topic({
        ros : ros,
        name : '/ui_guide',
        messageType : 'std_msgs/Int32'
      });

      ui_options = new ROSLIB.Topic({
        ros : ros,
        name : '/ui_options',
        messageType : 'std_msgs/Int32'
      });

      ui_thank = new ROSLIB.Topic({
        ros : ros,
        name : '/ui_thank',
        messageType : 'std_msgs/Int32'
      });

      ui_goal_reached = new ROSLIB.Topic({
        ros : ros,
        name : '/ui_goal_reached',
        messageType : 'std_msgs/Int32'
      });
      
      ui_nav_finish = new ROSLIB.Topic({
        ros : ros,
        name : '/ui_nav_finish',
        messageType : 'std_msgs/Int32'
      });
    

      ui_show_menu = new ROSLIB.Topic({
        ros : ros,
        name : '/ui_show_menu',
        messageType : 'std_msgs/Int32'
      });

      ui_rating = new ROSLIB.Topic({
        ros : ros,
        name : '/ui_rating',
        messageType : 'std_msgs/Int32'
      });

      ui_battery = new ROSLIB.Topic({
        ros : ros,
        name : '/ui_battery',
        messageType : 'std_msgs/Int32'
      });

      ui_error = new ROSLIB.Topic({
        ros : ros,
        name : '/ui_error',
        messageType : 'std_msgs/Int32'
      });
      
       ui_shutdown = new ROSLIB.Topic({
        ros : ros,
        name : '/ui_shutdown',
        messageType : 'std_msgs/Int32'
      }); 
    /*
      Subscribing to topics
    -------------------------- */
    /*ui_guide.subscribe(function(message) {
       console.log('Received message on ' + listener_ui_guide.name + ': ' + message.data);
       alert("I was listening to ui_guide topic. I got a message "+message.data);
       // listener.unsubscribe();
    });

    ui_nav.subscribe(function(message) {
       console.log('Received message on ' + listener_ui_nav.name + ': ' + message.data);
       alert("I was listening to ui_nav topic. I got a message "+message.data+" You will be redirect now");
       window.location = 'choice.htm'
       // listener.unsubscribe();
    });*/
    

    function showMenu(){
      // window.location = 'choice.htm'
      $('.class-allpage').css('display','none');
      $('.post-login').css('display','block');
      $('.container-choice').css('display','block');

      id_timeout = setTimeout(function(){
        goToMainPage();
      },8000);       //Delay 1

    }

      ui_show_menu.subscribe(function(message) {
         faceDetectSuccess();
         setTimeout(showMenu, 12000); //Delay 2
      });

      ui_battery.subscribe(function(message) {
         if(parseInt(message.data) == 1){
            $('.class-allpage').css('display','none')
            $('.container-battery-low').css('display','block');
         }else{
          $('.class-allpage').css('display','none')
            $('.container-index').css('display','block');
         }
      });

      ui_error.subscribe(function(message) {
         if(parseInt(message.data) == 1){
            $('.class-allpage').css('display','none');
            $('.container-error').css('display','block');
         }else{
          $('.class-allpage').css('display','none')
            $('.container-index').css('display','block');
         }
      });

      ui_nav_finish.subscribe(function(message) {
         console.log("received a message in ui_nav_finish");
         setTimeout(function(){
          $('.class-allpage').css('display','none')
          $('.container-reached').css('display','block');
	 },9500);  // delay for three option screen to appear
          id_timeout = setTimeout(function(){
            goToMainPage();
          },22000);  //Three option screen user timeout 
      });
  
       ui_goal_reached.subscribe(function(message) {
         console.log("received a message in ui_goal_reached");
         setTimeout(function(){
          goToRatingPage();
        },2500);
        id_timeout = setTimeout(function(){
          goToMainPage();
        },14000);     //Delay 4 -rate me screen timeout
      });

      ui_nav.subscribe(function(message) {
         console.log("Received a message from ui nav as below");
         console.log(message);
      });

      ui_guide.subscribe(function(message) {
         console.log("Received a message from ui guide as below");
         console.log(message);
      });

      ui_options.subscribe(function(message) {
         console.log("Received a message from ui_options as below");
         console.log(message);
      });
      
      ui_shutdown.subscribe(function(message) {
         console.log("Received a message from ui_options as below");
         console.log(message);
      });


    /*
      BUTTON CLICK EVENTS
    ------------------------------------------------------*/

    $('#choice_cash_withdrawal').on('click',function(){
      clearTimeout(id_timeout);
      console.log("cash Withdrawal got clicked");
      var data = 1;
      var json_data = { 'data' : data};
      ui_nav.publish(json_data);
      showPage(data);
    });

    $('#choice_cash_deposit').on('click',function(){
      clearTimeout(id_timeout);
      console.log("cash Deposit got clicked");
      var data = 2;
      var json_data = { 'data' : data};
      ui_nav.publish(json_data);
      showPage(data);
    });

    $('#choice_demat').on('click',function(){
      clearTimeout(id_timeout);
      console.log("Demat got clicked");
      var data = 3;
      var json_data = { 'data' : data};
      ui_nav.publish(json_data);
      showPage(data);
    });

    $('#choice_forex').on('click',function(){
      clearTimeout(id_timeout);
      console.log("Forex got clicked");
      var data = 4;
      var json_data = { 'data' : data};
      ui_nav.publish(json_data);
      showPage(data);
    });

    $('#choice_fixed_deposit').on('click',function(){
      clearTimeout(id_timeout);
      console.log("FD got clicked");
      var data = 5;
      var json_data = { 'data' : data};
      ui_nav.publish(json_data);
      showPage(data);
    });

    $('#choice_others').on('click',function(){
      clearTimeout(id_timeout);
      console.log("Others got clicked");
      var data = 6;
      var json_data = { 'data' : data};
      ui_nav.publish(json_data);
      showPage(data);
    });

    $('#repeat').on('click',function(){
      clearTimeout(id_timeout);
      var data = g_parameter;
      var json_data = { 'data' : data};
     
      ui_options.publish({ 'data' : 1});
       setTimeout(function(){
       ui_nav.publish(json_data)
       showPage(data)},1000);     //delay to publish the value to ui_nav for repeating
    });

    $('#takemethere').on('click',function(){
      clearTimeout(id_timeout);
      var data = g_parameter;
      var json_data = { 'data' : data};
      ui_options.publish({ 'data' : 2});
      showPage(data);
      id_timeout = setTimeout(function(){
           ui_guide.publish(json_data)  
          },10000);  //delay to publish the options 
     
      
     
    });


    $('#thankyou').on('click',function(){
      clearTimeout(id_timeout);
      var data = g_parameter;
      var json_data = { 'data' : data};
      ui_options.publish({ 'data' : 3});
        setTimeout(function(){
          goToRatingPage();
        },1000);
        id_timeout = setTimeout(function(){
          goToMainPage();
        },10000);     //Delay 4 -rate me screen timeout
    });

    $('.rating').on('click',function(){
      clearTimeout(id_timeout);
      console.log("clicked");
      var value = $('input[name=rating]:checked').val();
      var data = value;
      var json_data = { 'data' : parseInt(data)};
      ui_rating.publish(json_data);
        setTimeout(function(){
         $('.class-allpage').css('display','none')
         $('.container-thank').css('display','block');
	},1000);
	setTimeout(function(){
         goToMainPage();
        },5000); 
     
    });

    

    function scanFace(){
      $('.after-face-detect').css('display','none');
      $('.before-face-detect').css('display','block');
    }

    function faceDetectSuccess(){
      $('.before-face-detect').css('display','none');
      $('.after-face-detect').css('display','block');
    }

})//end of document.ready


function func()
{
   istrue = true;
   timer = setTimeout(function(){ makeChange();},delay);
}
function makeChange(){
  if(timer)
  clearTimeout(timer);
  
  if(istrue)
  {
      // $('.icon-power').toggleClass('off');
      //alert("Long press initiated");
      ui_shutdown.publish({ 'data' : 1});
  }
}
function revert()
{
   istrue =false;
}
// End Long press code



function scanFace(){
  $('.after-face-detect').css('display','none');
  $('.before-face-detect').css('display','block');
}

function showPage(action){

  console.log("SHOW PAGE GOT CALLED with action "+action);

  switch(action){
    case 1:
      g_parameter = 1;
      $('.class-allpage').css('display','none')
      $('.container-dummy').css('display','block');
      break;
    case 2:
      g_parameter = 2;
      $('.class-allpage').css('display','none')
      $('.container-dummy').css('display','block');
      break;
    case 3:
      g_parameter = 3;
      $('.class-allpage').css('display','none');
      $('.container-dummy').css('display','block');
      break;
    case 4:
      g_parameter = 4;
      $('.class-allpage').css('display','none');
      $('.container-dummy').css('display','block');
     break;
    case 5:
      g_parameter = 5;
      $('.class-allpage').css('display','none');
      $('.container-dummy').css('display','block');
      break;
    case 6:
      g_parameter = 6;
      $('.class-allpage').css('display','none');
      $('.container-dummy').css('display','block');
      break;
  }

  // $('.modal-map').css('display','block');

}

function hideModal(){
  // $('.modal-map').css('display','none');
}

function sendRating(){
  // var value = $('input[name=rating]:checked').val();
  // var data = 1;
  // var json_data = { 'data' : data};
  // ui_guide.publish(json_data);
}

g_data_to_publish = null;
g_rating_value = 0;

//Delay for the rating page
function goToRatingPage(){
  setTimeout(function(){
    // window.location = 'index.htm';
    $("input:radio").attr("checked", false);
    $('.class-allpage').css('display','none');
    $('.container-rating').css('display','block');
   }, 5000);   //Delay 5
}

function goToMainPage(){
  setTimeout(function(){
    // window.location = 'index.htm';
    $('.class-allpage').css('display','none');
    $('.post-login').css('display','none');
    $('.container-index').css('display','block')
    scanFace();
  }, 3000);   //Delay 5
}

function updateTime() {
    var currentTime = new Date();
    var hours = currentTime.getHours();
    var minutes = currentTime.getMinutes();
    var seconds = currentTime.getSeconds();
    if (minutes < 10){
        minutes = "0" + minutes;
    }
    if (seconds < 10){
        seconds = "0" + seconds;
    }
    var v = hours + ":" + minutes;
    if(hours > 11){
        v+=" PM";
    } else {
        v+=" AM"
    }
    
    

    setTimeout("updateTime()",1000);
    document.getElementById('time').innerHTML=v;

}

function getQueryParams(qs) {
    qs = qs.split('+').join(' ');
    var params = {},
        tokens,
        re = /[?&]?([^=]+)=([^&]*)/g;
    while (tokens = re.exec(qs)) {
        params[decodeURIComponent(tokens[1])] = decodeURIComponent(tokens[2]);
    }
    return params;
}

updateTime(); 
