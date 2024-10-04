[% IF whole.error %]
[% IF whole.status == 'missing_type' %]
<p><em>Please Note:</em> Mandatory field Type is missing.</p>
[% ELSE %]
<p>Unhandled error</p>
[% END %]
[% END %]

<h2>Edit a manual ILL request</h2>
<form id="mcpl_edit_form" method="POST" action=[% here %]>
  [% INCLUDE 'csrf-token.inc' %]
  <fieldset class="rows">
    <legend>General details</legend>
    <ol id="general-mcpl-fields">
      <li>
        <label class="required" for="type">Type:</label>
        <select name="type" id="type">
          <option value=""/>
          [% IF whole.value.other.type.lower == "book" %]
          <option value="book" selected="selected">Book</option>
          [% ELSE %]
          <option value="book">Book</option>
          [% END %]
          [% IF whole.value.other.type.lower == "lpbook" %]
          <option value="lpbook" selected="selected">Large Print Book</option>
          [% ELSE %]
          <option value="lpbook">Large Print Book</option>
          [% END %]
          [% IF whole.value.other.type.lower == "journal" %]
          <option value="journal" selected="selected">Journal</option>
          [% ELSE %]
          <option value="journal">Journal</option>
          [% END %]
          [% IF whole.value.other.type.lower == "dvd" %]
          <option value="dvd" selected="selected">DVD</option>
          [% ELSE %]
          <option value="dvd">DVD</option>
          [% END %]
          [% IF whole.value.other.type.lower == "vgame" %]
          <option value="vgame" selected="selected">Video Game</option>
          [% ELSE %]
          <option value="vgame">Video Game</option>
          [% END %]
          [% IF whole.value.other.type.lower == "abook" %]
          <option value="abook" selected="selected">Audiobook</option>
          [% ELSE %]
          <option value="abook">Audiobook</option>
          [% END %]
          [% IF whole.value.other.type.lower == "cd" %]
          <option value="cd" selected="selected">Music CD</option>
          [% ELSE %]
          <option value="cd">Music CD</option>
          [% END %]
        </select>
      </li>
    </ol>
  </fieldset>
  [% cwd = whole.cwd %]
  [% type = whole.value.other.type %]
  [% IF type %]
      [% INCLUDE "${cwd}/shared-includes/forms/${type}.inc" %]
  [% END %]
  [% INCLUDE "${cwd}/shared-includes/custom_fields.inc" %]
  <fieldset class="action">
    <input id="ill-submit" type="submit" value="Update"/>
    <a class="cancel" href="/cgi-bin/koha/ill/ill-requests.pl">Cancel</a>
  </fieldset>
  <input type="hidden" name="illrequest_id" value="[% whole.value.other.illrequest_id %]" />
  <input type="hidden" name="op" value="cud-edititem" />
  <input type="hidden" name="stage" value="form" />
  <input type="hidden" name="backend" value="Mcpl" />
</form>
[% BLOCK backend_jsinclude %]
<script type="text/javascript">
    // <![CDATA[]
    [% INCLUDE "${cwd}/shared-includes/shared.js" %]
    // ]]>
</script>
[% END %]
