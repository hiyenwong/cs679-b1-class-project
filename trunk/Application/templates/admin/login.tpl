{include file='header.tpl'}

<div id="status">{$errorMessage}</div>

<form method="post">
	<input type="hidden" name="ref" id="ref" value="{$ref}" />
	<table>
		<tr>
			<th class="rightalign">Username</th>
			<td><input type="text" name="username" id="username" class="inputwidth" /></td>
		</tr>
		<tr>
			<th class="rightalign">Password</th>
			<td><input type="password" name="password" id="password" class="inputwidth" /></td>
		</tr>
		<tr>
			<td colspan="2" class="rightalign"><input type="submit" name="submitted" id="submitted" value="Login" class="button" /></td>
		</tr>
	</table>
</form>

{include file='footer.tpl'}