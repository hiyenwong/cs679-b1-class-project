<?php

require_once $SMARTY_DIR . '/Smarty.class.php';

class MySmarty extends Smarty {
	function MySmarty(array $SMARTY_CONFIG = null) {
		parent::__construct();

		if ($SMARTY_CONFIG) {
			$this->template_dir = $SMARTY_CONFIG['TEMPLATE'];
			$this->compile_dir = $SMARTY_CONFIG['COMPILE'];
			$this->cache_dir = $SMARTY_CONFIG['CACHE'];
			$this->config_dir = $SMARTY_CONFIG['CONFIG'];
			$this->caching = $SMARTY_CONFIG['CACHE'] ? $SMARTY_CONFIG['CACHE'] : false;

			$this->assign ('version', $SMARTY_CONFIG['VERSION']);
			$this->assign ('base_url', $SMARTY_CONFIG['BASE_URL']);
			$this->assign ('image_url', $SMARTY_CONFIG['IMAGE_URL']);
			$this->assign ('style_url', $SMARTY_CONFIG['STYLE_URL']);
			$this->assign ('js_url', $SMARTY_CONFIG['JS_URL']);
			$this->assign ('system_url', $SMARTY_CONFIG['SYSTEM_URL']);
			$this->assign ('redirect_url', $SMARTY_CONFIG['REDIRECT_URL']);
			$this->assign ('webmaster', $SMARTY_CONFIG['WEBMASTER']);
			$this->assign ('max_upload_size', $SMARTY_CONFIG['MAX_UPLOAD_SIZE']);
			$this->assign ('max_upload_parsed', $SMARTY_CONFIG['MAX_UPLOAD_PARSED']);
			$this->assign ('max_attachments', $SMARTY_CONFIG['MAX_ATTACHMENTS']);

			if (isset ($_SERVER ['REQUEST_URI'])) {
				$this->assign ('login_url', $SMARTY_CONFIG['LOGIN_URL'] . '?ref=' . base64_encode ($_SERVER ['REQUEST_URI']));
			} else {
				$this->assign ('login_url', $SMARTY_CONFIG['LOGIN_URL']);
			}

			$this->assign ('logout_url', $SMARTY_CONFIG['LOGOUT_URL']);

		}

		$this->allow_php_tag=true;
	}
}
?>