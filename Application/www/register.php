<?php
	require_once '../includes/config.inc';
	require_once 'user.inc';
    require_once 'factory.inc';
    require_once 'view.inc';
    require_once 'transaction.inc';
	
    if (!empty($_POST)) {
        
	try {
	
        $username = htmlentities($_POST['username']);
	    $password = htmlentities($_POST['password']);
	    $passwordRepeat = htmlentities($_POST['passwordRepeat']);
	   
	    if ($passwordRepeat !== $password) {
	       //TODO: error
	    }
	    
	    //if (User::isUsernameTaken($username)) {
	       //TODO: error
	    //}
	
        $t = new Transaction(new MySqlDB());
        $t->start();
        
		$user = Factory::createView(new UserKey());
			    
        $date = new DateTime();
        
	    $user->setUsername($username);
	    $user->setPassword($password);
	    $user->setActive(true);
	    $user->setCreateDate($date->getTimestamp());
	    $user->setLastLoginDate($date->getTimestamp());
	    $user->setNumberOfAttempts(1);
	    $user->setFirstName('jon');
        $user->setLastName('reimels');
   

	    $t->commit();

	} catch (Exception $e) {
	    print_r($e);
		echo 'Internal Error occurred, please email administrator for further assistance.';
	}

	   
	}
	
	$smarty = new MySmarty($SMARTY_CONFIG);
	$smarty->display('register.tpl');
	
?>