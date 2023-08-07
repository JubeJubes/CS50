select j1.title from(
    select title from movies
    join stars on movies.id = stars.movie_id
    join people on stars.person_id = people.id
    where name = 'Johnny Depp') as j1
join (
    select title from movies
    join stars on movies.id = stars.movie_id
    join people on stars.person_id = people.id
    where name = 'Helena Bonham Carter') as h1
on j1.title = h1.title;

