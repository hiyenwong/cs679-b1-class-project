<?php
	require_once '../includes/config.inc';
	require_once 'user.inc';
	require_once 'date.inc';
    require_once 'factory.inc';
    require_once 'view.inc';
    require_once 'transaction.inc';
	
    if (!empty($_POST)) {
        
	try {
	
        $username = htmlentities($_POST['username']);
	    $password = htmlentities($_POST['password']);
	    $firstname = 'Churk';
	    $lastname = 'Leung';
	    $passwordRepeat = htmlentities($_POST['password_repeat']);
	   
	    if ($passwordRepeat !== $password) {
	       //TODO: error
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

	} catch (Exception $e) {
	    echo "<PRE>" . $e->getMessage() . "\n" . $e->getTraceAsString() . "\n" . print_r ($e, true) . "</PRE>";
		echo 'Internal Error occurred, please email administrator for further assistance.';
	}

	   
	}
	
	$smarty = new MySmarty($SMARTY_CONFIG);
	$smarty->display('register.tpl');
	
?>