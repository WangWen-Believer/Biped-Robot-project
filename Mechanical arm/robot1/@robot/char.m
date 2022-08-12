%CHAR String representation of robot parametesrs

% $Log: char.m,v $
% Revision 1.3  2002/04/01 12:02:27  pic
% General tidyup, comments, clarification, copyright, see also, RCS keys.
%
% $Revision: 1.3 $
% Copyright (C) 1999-2002, by Peter I. Corke

function s = char(r)

	% build a configuration string
	rp = [];
	for i = 1:r.n,
		rp = [rp r.link{i}.RP];
	end

	s = sprintf('%s (%d axis, %s)', r.name, r.n, rp);

	if ~isempty(r.manuf)
		s = strcat(s, [' [' r.manuf ']']);
	end
	if ~isempty(r.comment)
		s = strcat(s, [' <' r.comment '>']);
	end
	s = strcat(s, sprintf('\n\t\tgrav = [%.2f %.2f %.2f]\n', r.gravity));
	if getfield(r, 'mdh') == 0,
		s = strcat(s, sprintf('\t\tstandard D&H parameters\n'));
	else
		s = strcat(s, sprintf('\t\tmodified D&H parameters\n'));
	end

	s = strcat(s, sprintf('\n\n  alpha\t\t A\t\t theta\t\t D\t\tR/P\n'));
	for i = 1:r.n,
		s = strcat(s, sprintf('\n%s', char(r.link{i})));
	end
