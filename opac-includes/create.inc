[% IF whole.error %]
[% IF whole.status == 'missing_identifier' %]
<p><em>Please Note:</em> Mandatory field Identifier is missing.</p>
[% ELSIF whole.status == 'missing_branch' %]
<p><em>Please Note:</em> Branch is a mandatory field.</p>
[% ELSIF whole.status == 'invalid_borrower' %]
<p><em>Please Note:</em> The borrower details you entered are invalid.</p>
[% ELSIF whole.status == 'invalid_branch' %]
<p><em>Please Note:</em> The branch you chose is invalid.</p>
[% ELSE %]
<p>Unhandled error</p>
[% END %]
[% END %]

[% IF whole.stage == "form" %]
<h2>Create a manual ILL request</h2>
<form id="create_form" method="POST" action=[% here %]>
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
  <fieldset class="rows">
    <legend>Patron options</legend>
    <ol>
      <li>
        <label class="required" for="branchcode">Destination library:</label>
        <select id="branchcode" name="branchcode">
          <option value="" />
          [% FOREACH branch IN branches %]
            [% IF whole.value.other.branchcode && branch.branchcode == whole.value.other.branchcode %]
            <option value="[% branch.branchcode %]" selected>
              [% branch.branchname %]
            </option>
            [% ELSE %]
            <option value="[% branch.branchcode %]">
              [% branch.branchname %]
            </option>
            [% END %]
          [% END %]
        </select>
      </li>
    </ol>
  </fieldset>

  <fieldset class="action">
    <input id="ill-submit" class="btn btn-default" type="submit" value="Create"/>
    <a class="cancel" href="/cgi-bin/koha/opac-illrequests.pl">Cancel</a>
  </fieldset>
  <input type="hidden" name="op" value="cud-create" />
  <input type="hidden" name="stage" value="form" />
  <input type="hidden" name="backend" value="Mcpl" />
</form>

[% ELSE %]
<p>Unknown stage.  This should not have happened.

[% END %]
[% BLOCK backend_jsinclude %]
<script type="text/javascript">
    // <![CDATA[]
    [% INCLUDE "${cwd}/shared-includes/shared.js" %]
    // ]]>
</script>
[% END %]
