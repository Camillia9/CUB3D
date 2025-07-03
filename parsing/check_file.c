#include "../includes/cub3d.h"


//bool	is_xpm_file(char *argv)
//{
//	size_t	len;

//	len = ft_strlen(argv);
//	if ((argv[len - 3] != 'x' || argv[len - 2] != 'p'
//			|| argv[len - 1] != 'm'
//			|| argv[len - 4] != '.'))
//		return (false);
//	return (true);
//}

//bool	is_dir(char *argv)
//{
//	int		fd;
//	bool	ret;

//	ret = false;
//	fd = open(argv, O_DIRECTORY);
//	if (fd >= 0)
//	{
//		close (fd);
//		ret = true;
//	}
//	return (ret);
//}

//int	check_file(char *argv, bool cub)
//{
//	int	fd;

//	if (is_dir(argv))
//		return (ft_putstr_fd("ERR_FILE_IS_DIR", 2), 1);
//	fd = open(argv, O_RDONLY);
//	if (fd == -1)
//		return (printf("erreur"), 1);
//	close(fd);
//	if (cub && !is_cub_file(argv))
//		return (printf("error : file not .cub"), 1);
//	if (!cub && !is_xpm_file(argv))
//		return (printf("ERR_FILE_NOT_XPM"), 1);
//	return (0);
//}


//Validation du nombre d'arguments : Vérifie qu'il y a exactement 1 argument (le fichier .cub)
//Vérification de l'extension : S'assure que le fichier se termine par .cub
//Test d'existence et de lisibilité : Utilise open() pour vérifier que le fichier peut être lu
//Gestion d'erreurs : Affiche "Error\n" suivi du message d'erreur et termine le programme

//Structure du code :

//print_error() : Fonction utilitaire pour afficher les erreurs au bon format
//check_file_extension() : Valide l'extension .cub
//check_file_access() : Teste l'ouverture du fichier
//validate_arguments() : Fonction principale de validation
//main() : Point d'entrée avec exemple d'utilisation

/**
 * Affiche un message d'erreur formaté et termine le programme
 */
void print_error(const char *message)
{
    printf("Error\n%s\n", message);
    exit(1);
}

/**
 * Vérifie que le fichier a l'extension .cub
 */
int check_file_extension(char *filename)
{
    int	len;

	len = ft_strlen(filename);
    
    // Vérifier que le nom fait au moins 5 caractères (.cub = 4 + au moins 1 pour le nom)
    if (len < 5)
        return (0);
    
    // Vérifier l'extension .cub à la fin
    if (ft_strcmp(filename + len - 4, ".cub") != 0)
        return (0);
    
    return (1);
}
/**
 * Vérifie que le fichier existe et est lisible
 */
int check_file_access(char *filename)
{
    int fd;
    
    // Tenter d'ouvrir le fichier en lecture
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (0);
    
    close(fd);
    return (1);
}

/**
 * Valide les arguments passés au programme
 */
void validate_arguments(int argc, char **argv)
{
    // Vérifier qu'il y a exactement 1 argument (+ le nom du programme = 2 total)
    if (argc != 2)
    {
        print_error("Usage: ./cub3d <map.cub>");
    }
    
    // Vérifier l'extension du fichier
    if (!check_file_extension(argv[1]))
    {
        print_error("Map file must have .cub extension");
    }
    
    // Vérifier que le fichier existe et est lisible
    if (!check_file_access(argv[1]))
    {
        print_error("Cannot open map file: file does not exist or is not readable");
    }
    
    printf("✓ Arguments validation successful!\n");
    printf("Map file: %s\n", argv[1]);
}
