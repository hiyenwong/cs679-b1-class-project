<?php
	require_once '../includes/config.inc';
	require_once 'user.inc';
	require_once 'date.inc';
    require_once 'factory.inc';
    require_once 'view.inc';
    require_once 'transaction.inc';
    
    $smarty = new MySmarty($SMARTY_CONFIG);
	
    if (!empty($_POST)) {
        
    	try {
            $action = htmlentities($_POST['action']);
            $username = htmlentities($_POST['username']);
            
            if ($action === "checkuser") {
                echo json_encode(User::isUsernameTaken($username));
                return;
            } elseif ($action === "adduser") {
        	    $password = htmlentities($_POST['password']);
        	    $passwordRepeat = htmlentities($_POST['password_repeat']);
        	    $firstname = htmlentities($_POST['firstname']);
        	    $lastname = htmlentities($_POST['lastname']);
    
                //check passwords are equal
        	    if ($passwordRepeat !== $password) {
                    $smarty->display('error.tpl');
                    return;
        	    }
        	    
        	    //check username is available
        	    if (User::isUsernameTaken($username)) {
                    $smarty->display('error.tpl');
                    return;
                }
                
                //check username is email
                if (!preg_match("/^[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,4}$/i", $username)) {
                    $smarty->display('error.tpl');
                    return;
                }
                
                //check password meets standards
                if (!preg_match("/((?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[^a-zA-Z0-9\s]).{8,})/", $password)) {
                    $smarty->display('error.tpl');
                    return;
                }
                    	   
                $t = new Transaction(new MySqlDB());
                $t->start();
                
        		$user = Factory::createView(new UserKey());
        			    
                $date = new Date();
                
        	    $user->setUsername($username);
        	    $user->setPassword($password);
        	    $user->setActive(true);
        	    $user->setCreatedDate($date->getTimestamp());
        	    $user->setLastLoginDate($date->getTimestamp());
        	    $user->setNumberOfAttempts(1);
        	    $user->setFirstName($firstname);
                $user->setLastName($lastname);
           
        	    $t->commit();

                header( 'Location: userpage.php' ) ;
    	    	return;
    	    }
    
    	} catch (Exception $e) {
    	    echo "<PRE>" . $e->getMessage() . "\n" . $e->getTraceAsString() . "\n" . print_r ($e, true) . "</PRE>";
    		echo 'Internal Error occurred, please email administrator for further assistance.';
    	}
 
	}
	
	$smarty->display('register.tpl');
	
?>