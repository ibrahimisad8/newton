<?php

ini_set('display_errors', 1);

ini_set('error_reporting', E_ERROR);

        $name    = 'Ibrahim isa';
        $to      = "ibrahimd8@yahoo.com";
        $subject = 'Job Interview notice';
        $message = "
                       <style>
                          .logo{ padding:9px 9px 15px 9px}
                       </style>
                       <body>
                            <div class='logo'>
                                <img src='http://www.iblynks.com/newton/images/newton-logo.png' />
                            </div>
                            <div>
                                Hello, $name <br/><br/>

                                Hi jus testing the system

                                <br/><br/>
                                Thank you!
                                <br/>
                                <b>Manager</b>  



                                <br/><br/><br/>
                                Alkifaya Logistic Company &raquo; <br/>
                                Support Center: Sadiq Sy<br/> 
                                Tel: +60128945034<br/>
                                Fax: 013-3840048290<br/>
                            </div>
                        </body>
                  ";
        $headers = array('From:Newton Agency <newton@iblynks.com>', 'Content-type: text/html');
        
        $mail    = mail($to, $subject, $message, implode("\r\n", $headers));
        
        if($mail)
        {
          $message = 'Message has been sent';    
        }
        else
        {
          $message = 'An error occured';
        }

?>
<html>
    <body>
        <div><?php echo $message?></div>
    </body>
</html>