<?php
	require_once '../includes/config.inc';
	require_once '../includes/access.inc';
	
	$requestedUrl = isset($_REQUEST['ref']) ? base64_decode(htmlentities($_REQUEST['ref'])) : $BASE_URL;
    $submitted = isset($_REQUEST['submitted']);
    $username = isset($_REQUEST['username']) ? htmlentities($_REQUEST['username']) : false;
    $password = isset($_REQUEST['password']) ? htmlentities($_REQUEST['password']) : false;
    
    $smarty = new MySmarty($SMARTY_CONFIG);
    
    if ($submitted) { 
        try {
            $access = new Access();
            if ($access->authenticate($username, $password)) {
                header ("Location: " . $requestedUrl);
                exit();
            } else {
                $smarty->assign('errorMessage', 'Username or Password is incorrect. Please try logging in again.');
            }
            
        } catch (AccessDeniedException $e) {
            header ('HTTP/1.1 401 Access Denied');
            echo "AccessDeniedException: " . $e->getMessage ();
        } catch (Exception $e) {
            header ('HTTP/1.1 500 Internal Server Error');
            echo "Exception: " . $e->getMessage ();
        }
    }
    
	$smarty->display('login.tpl');
	
?>